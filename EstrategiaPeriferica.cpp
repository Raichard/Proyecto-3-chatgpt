#include "EstrategiaPeriferica.h"

void EstrategiaPeriferica::realizarMovimiento(Juego* juego) {
    Tablero* tablero = juego->obtenerTablero();
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    for (int i = 0; i < filas; ++i) {
        if (tablero->esMovimientoValido(i, 0, i, 1) && !juego->dejaCasillaDisponibleParaOponente(i, 0, i, 1) && juego->hacerMovimiento(i, 0, i, 1)) {
            return;
        }
        if (tablero->esMovimientoValido(i, columnas - 1, i, columnas - 2) && !juego->dejaCasillaDisponibleParaOponente(i, columnas - 1, i, columnas - 2) && juego->hacerMovimiento(i, columnas - 1, i, columnas - 2)) {
            return;
        }
    }

    for (int j = 0; j < columnas; ++j) {
        if (tablero->esMovimientoValido(0, j, 1, j) && !juego->dejaCasillaDisponibleParaOponente(0, j, 1, j) && juego->hacerMovimiento(0, j, 1, j)) {
            return;
        }
        if (tablero->esMovimientoValido(filas - 1, j, filas - 2, j) && !juego->dejaCasillaDisponibleParaOponente(filas - 1, j, filas - 2, j) && juego->hacerMovimiento(filas - 1, j, filas - 2, j)) {
            return;
        }
    }

    // Si no se encontró un movimiento seguro en la periferia, realizar un movimiento aleatorio seguro
    EstrategiaAleatoria* aleatoria = new EstrategiaAleatoria();
    aleatoria->realizarMovimientoAleatorioSeguro(juego);
}

