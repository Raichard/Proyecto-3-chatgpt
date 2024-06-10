#include "EstrategiaCentral.h"

void EstrategiaCentral::realizarMovimiento(Juego* juego) {
    Tablero* tablero = juego->obtenerTablero();
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();
    int centroFila = filas / 2;
    int centroColumna = columnas / 2;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (tablero->esMovimientoValido(centroFila + i, centroColumna + j, centroFila + i + 1, centroColumna + j) &&
                !juego->dejaCasillaDisponibleParaOponente(centroFila + i, centroColumna + j, centroFila + i + 1, centroColumna + j) &&
                juego->hacerMovimiento(centroFila + i, centroColumna + j, centroFila + i + 1, centroColumna + j)) {
                return;
            }
            if (tablero->esMovimientoValido(centroFila + i, centroColumna + j, centroFila + i, centroColumna + j + 1) &&
                !juego->dejaCasillaDisponibleParaOponente(centroFila + i, centroColumna + j, centroFila + i, centroColumna + j + 1) &&
                juego->hacerMovimiento(centroFila + i, centroColumna + j, centroFila + i, centroColumna + j + 1)) {
                return;
            }
        }
    }

    EstrategiaAleatoria* aleatorio = new EstrategiaAleatoria();
    aleatorio->realizarMovimientoAleatorioSeguro(juego);
}

