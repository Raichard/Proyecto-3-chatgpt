#pragma once
#include "Tablero.h"

class IteradorTablero {
private:
    Tablero* tablero;
    int filaActual;
    int columnaActual;

public:
    IteradorTablero(Tablero* tablero);
    void primero();
    void siguiente();
    bool esFin();
    char actual();
    int getFilaActual();
    int getColumnaActual();
};
