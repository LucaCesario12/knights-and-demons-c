#include "tablero.h"
#include "juego.h"


Tablero *CrearTablero(int n_filas, int n_columnas, int n_pikas)
{
    Tablero *t = malloc(sizeof(Tablero));
    if(!t)
        return NULL;
    t->filas = n_filas;
    t->columnas = n_columnas;
    t->caballeros = 0;
    t->demonios = 0;
    t->pikas = n_pikas;
    t->mat = malloc(sizeof(char*) * n_filas);
    if(!t->mat)
    {
        free(t);
        return NULL;
    }
    for(size_t i = 0; i < n_filas; i++)
    {
        t->mat[i] = malloc(sizeof(char) * n_columnas);
        if(!t->mat[i])
        {
            DestruirTablero(t, i);
            return NULL;
        }
    }
    return t;
}

void InicializarTablero(Tablero *t)
{
    if (!t || !t->mat)
        return;

    srand(time(NULL));  // inicializa la semilla solo una vez por ejecución

    for (int i = 0; i < t->filas; i++)
    {
        for (int j = 0; j < t->columnas; j++)
        {
            int aleatorio = rand() % 2;  // genera 0 o 1
            t->mat[i][j] = (aleatorio == 0) ? 'D' : 'C'; // Si es 0 va D, sino C
        }
    }
}

void ContarUnidades(Tablero *t)
{
    for(int i = 0; i < t->filas; i++)
    {
        for(int j = 0; j < t->columnas; j++)
        {
            if(t->mat[i][j] == 'D')
                t->demonios++;
            else
                t->caballeros++;
        }
    }
}

void Movimiento(Tablero *t, int *fila, int *columna)
{
        char tecla = getch();
        int nuevaFila = *fila;
        int nuevaCol = *columna;

        switch (tecla)
        {
            case 'w': case 'W': nuevaFila--; break;
            case 's': case 'S': nuevaFila++; break;
            case 'a': case 'A': nuevaCol--; break;
            case 'd': case 'D': nuevaCol++; break;
            case 'q': case 'Q': 
                if(t->pikas > 0)
                {
                    UtilizarPika(t, *fila, *columna);
                    t->pikas--;
                }
                else
                {
                    printf("\n No te quedan mas pikas disponibles!\n");
                    Sleep(1000);
                }
                break;
            case 13: // ENTER
                Intercambio(t, *fila, *columna);
                return;
            default: return; // tecla no válida
        }

        // Verificar límites del tablero
        if (nuevaFila >= 0 && nuevaFila < t->filas && nuevaCol >= 0 && nuevaCol < t->columnas)
        {      // limpiar posición anterior
            *fila = nuevaFila;
            *columna = nuevaCol;     // colocar jugador
        }
}

void UtilizarPika(Tablero *t, int fila, int columna)
{
    if(t->mat[fila][columna] == 'D')
    {
        t->mat[fila][columna] = 'C';
        t->caballeros++;
        t->demonios--;
    }
    else
    {
        t->mat[fila][columna] = 'D';
        t->caballeros--;
        t->demonios++;
    }
}

void Intercambio(Tablero *t, int fila, int columna)
{
    int movFila[] = {-1, 1, 0 ,0};
    int movCol[] = {0, 0, -1, 1};
    if(t->mat[fila][columna] == 'D')
    {
        t->mat[fila][columna] = 'C';
        t->caballeros++;
        t->demonios--;
    }
    else
    {
        t->mat[fila][columna] = 'D';
        t->caballeros--;
        t->demonios++;
    }

    for(int i = 0; i < 4; i++) // deberia ser un define
    {
        int nFila = fila + movFila[i];
        int nColumna = columna + movCol[i];
        if(nFila >= 0 && nFila < t->filas && nColumna >= 0 && nColumna < t->columnas) // verifica el borde
        {
            if(t->mat[nFila][nColumna] == 'D')
            {
                t->mat[nFila][nColumna] = 'C';
                t->caballeros++;
                t->demonios--;
            }
            else
            {
                t->mat[nFila][nColumna] = 'D';
                t->caballeros--;
                t->demonios++;
            }

        }
    }
}

void MostrarTablero(Tablero *t, int cursorFila, int cursorColumna)
{
    system("cls");

    if(!t || !t->mat)
        return;
    printf("KNIGHTS AND DEMONS\n");
    printf("Pikas Disponibles: %d\n", t->pikas);
    for(int i = 0; i < t->filas; i++)
    {
        printf(" ");
        for(int j = 0; j < t->columnas; j++)
        {
            if(i == cursorFila && j == cursorColumna)
                printf("\033[30m\033[47m %c \033[0m", t->mat[i][j]);
            else
                printf(" %c ", t->mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DestruirTablero(Tablero *t, int n_columnas_creadas)
{
    for(size_t i = 0; i < n_columnas_creadas; i++)
    {
        free(t->mat[i]);
    }
    t->columnas = 0;
    t->filas = 0;
    free(t->mat);
    free(t);
}


