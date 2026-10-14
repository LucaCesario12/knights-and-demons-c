#include "juego.h"
#include "menu.h"
#include "tablero.h"
#include <time.h>

void IniciarPartida(int eleccion, bool *estado, bool *partida, int *juego, int *pikas_actuales)
{
    Tablero *t;
    int filas, columnas;
    time_t Limite;
    int restante;
    if(eleccion == 1)
    {
        t = CrearTablero(FILAS_LVL1, COLUMNAS_LVL1, (*juego > 0) ? *pikas_actuales : N_PIKASLVL1);
        filas = 2;
        columnas = 2;
        Limite = IniciarTemporizador(TIEMPO_LVL1);
    }
    if(eleccion == 2)
    {
        t = CrearTablero(FILAS_LVL2, COLUMNAS_LVL2, (*juego > 0) ? *pikas_actuales : N_PIKASLVL2);
        filas = 4;
        columnas = 4;
        Limite = IniciarTemporizador(TIEMPO_LVL2);
    }
    if(eleccion == 3)
    {
        t = CrearTablero(FILAS_LVL3, COLUMNAS_LVL3, (*juego > 0) ? *pikas_actuales : N_PIKASLVL3);
        filas = 5;
        columnas = 5;
        Limite = IniciarTemporizador(TIEMPO_LVL3);
    }
    if(eleccion == 4)
    {
        *partida = false;
        *estado = false;
        return;
    }
    if(!t)
        return;

    InicializarTablero(t);
    ContarUnidades(t);
    restante = IniciarTemporizador(Limite);
    while(t->caballeros != 0 && t->demonios != 0 && restante != 0)
    {
        MostrarTablero(t, filas, columnas);
        MostrarBarra(t);
        restante = Tiempo_Restante(Limite);
        MostrarTemporizador(restante);
        Movimiento(t, &filas, &columnas);
        Sleep(200);
    }
    FinPartida(t, estado, juego, restante);
    *pikas_actuales = t->pikas;
    DestruirTablero(t, columnas);
}


void MostrarBarra(Tablero *t)
{
    int total = t->caballeros + t->demonios;
    if(total == 0)
    {
        printf("Sin datos aun.\n");
        return;
    }

    float proporcionCaballeros = (float)t->caballeros / total;
    int barraCaballeros = (int)(proporcionCaballeros * 30);
    int barraDemonios = 30 - barraCaballeros;

    printf("\nCABALLEROS [%.*s%.*s] DEMONIOS\n",
        barraCaballeros, "==============================",
        barraDemonios,   "------------------------------");
}

time_t IniciarTemporizador(int segundos)
{
    return time(NULL)+ segundos;
}

time_t Tiempo_Restante(time_t Limite)
{
    time_t Ahora = time(NULL); //tiempo actual
    if(Ahora >= Limite)
            return 0;
    return Limite - Ahora; //tiempo restante
}
void MostrarTemporizador(time_t restante)
{
    printf("\nTiempo restante: %d \n", (int)restante);
    puts("----------------------------");
}

void FinPartida(Tablero *t, bool *estado, int *juego, int restante)
{
    if(t->demonios == 0)
    {
        puts("HAS GANADO DEL LADO DE LOS BUENOS");
        puts("Preparate para otra partida...");
        puts("Has obtenido una pika extra!");
        t->pikas++;

        puts("Si desea volver al menu pulse --> 0");
        char ch = getch();
        if(ch == '0')
        {
            *estado = false;
        }
        else
        {
           (*juego)++;
        }
    }
    if(t->caballeros == 0)
    {
        puts("HAS PERDIDO, LOS DEMONIOS TE HAN CONQUISTADO");
        puts("Preparate para otra partida...");
        puts("Si desea volver al menu pulse --> 0");
        char ch = getch();
        if(ch == '0')
        {
            *estado = false;
        }
        else
        {
           (*juego)++;
        }
    }
    if(restante <= 0)
    {
        puts("TE HAS QUEDADO SIN TIEMPO!");
        Sleep(5000);
        *estado = false;
    }
}
