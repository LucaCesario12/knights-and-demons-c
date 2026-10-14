#include "menu.h"

int GenerarMenu()
{
    int eleccion = 0;

    puts("BIENVENIDO A KNIGHTS AND DEMONS\n");
    puts("--------------------------------\n");
    puts("Seleccione el nivel de dificultad\n");

    puts("Facil --> 1\n");
    puts("Intermedio --> 2\n");
    puts("Dificil --> 3\n");
    puts("Salir --> 4\n");

    scanf("%d", &eleccion);

    return eleccion;
}