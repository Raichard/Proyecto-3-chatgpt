#include "IteradorTablero.h"

IteradorTablero::IteradorTablero(Tablero* tab) {
    tablero = tab;
    filaActual = 0;
    columnaActual = 0;
}

void IteradorTablero::primero() {
    filaActual = 0;
    columnaActual = 0;
}

void IteradorTablero::siguiente() {
    if (columnaActual < tablero->getColumnas() * 2 - 2) {
        columnaActual++;
    }
    else if (filaActual < tablero->getFilas() * 2 - 2) {
        columnaActual = 0;
        filaActual++;
    }
    else {
        filaActual++;
        columnaActual++;
    }
}

bool IteradorTablero::esFin() {
    return filaActual == tablero->getFilas() * 2 - 1 && columnaActual == tablero->getColumnas() * 2 - 1;
}

char IteradorTablero::actual() {
    return *tablero->getCelda(filaActual, columnaActual);
}

int IteradorTablero::getFilaActual() {
    return filaActual;
}

int IteradorTablero::getColumnaActual() {
    return columnaActual;
}
