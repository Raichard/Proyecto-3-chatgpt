#include "EstrategiaIslas.h"

void EstrategiaIslas::realizarMovimiento(Juego* juego) {
    Tablero* tablero = juego->obtenerTablero();
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();

    for (int i = 1; i < filas - 1; ++i) {
        for (int j = 1; j < columnas - 1; ++j) {
            if (tablero->esMovimientoValido(i, j, i + 1, j) &&
                !juego->dejaCasillaDisponibleParaOponente(i, j, i + 1, j) &&
                juego->hacerMovimiento(i, j, i + 1, j)) {
                return;
            }
            if (tablero->esMovimientoValido(i, j, i, j + 1) &&
                !juego->dejaCasillaDisponibleParaOponente(i, j, i, j + 1) &&
                juego->hacerMovimiento(i, j, i, j + 1)) {
                return;
            }
        }
    }

    EstrategiaAleatoria* aleatorio = new EstrategiaAleatoria();
    aleatorio->realizarMovimientoAleatorioSeguro(juego);
}

