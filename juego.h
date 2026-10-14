#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "estructuras.h"
#include <time.h>
#include <stdbool.h>

#define BAR_LENGTH 50 // Marco fijo de la barra

void IniciarPartida(int eleccion, bool *estado, bool *partida, int *juego, int *pikas_actuales);
time_t IniciarTemporizador(int segundos);
void MostrarBarra(Tablero *t);
void MostrarTemporizador(time_t restante);
time_t Tiempo_Restante(time_t limite);
void FinPartida(Tablero *t, bool *flag, int *juego, int restante);



#endif // JUEGO_H_INCLUDED
