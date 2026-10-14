#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "estructuras.h"

#define FILAS_LVL1 5
#define COLUMNAS_LVL1 5
#define N_PIKASLVL1 6
#define FILAS_LVL2 8
#define COLUMNAS_LVL2 8
#define N_PIKASLVL2 4
#define FILAS_LVL3 10
#define COLUMNAS_LVL3 10
#define N_PIKASLVL3 2
#define TIEMPO_LVL1 10
#define TIEMPO_LVL2 240
#define TIEMPO_LVL3 180

Tablero *CrearTablero(int n_filas, int n_columnas, int n_pikas);
void InicializarTablero(Tablero *t);
void ContarUnidades(Tablero *t);
void Movimiento(Tablero *t, int *fila, int *columna);
void Intercambio(Tablero *t, int fila, int columna);
void UtilizarPika(Tablero *t, int fila, int columna);
void MostrarTablero(Tablero *t, int fila, int columna);
void DestruirTablero(Tablero *t, int n_columnas_creadas);

#endif // TABLERO_H_INCLUDED
