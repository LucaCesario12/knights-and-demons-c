#include "tablero.h"
#include "juego.h"
#include "menu.h"

int main()
{
    bool partida = true;
    while(partida)
    {
        bool estado = true;
        int juego = 0, pikas_actuales = 0;
        int eleccion = GenerarMenu();
        while(estado)
        {
        IniciarPartida(eleccion, &estado, &partida, &juego, &pikas_actuales);
        }
    }
}
