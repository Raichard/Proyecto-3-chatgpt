
#include "EstrategiaCercana.h"

void EstrategiaCercana::realizarMovimiento(Juego* juego) {
    Tablero* tablero = juego->obtenerTablero();
    Jugador* jugadorOponente;

    if (juego->obtenerJugador1() == juego->obtenerJugadorActual()) {
        jugadorOponente = juego->obtenerJugador2();
    }
    else {
        jugadorOponente = juego->obtenerJugador1();
    }

    Movimiento ultimaJugadaOponente = jugadorOponente->obtenerUltimaJugada();

    int x1 = ultimaJugadaOponente.x1;
    int y1 = ultimaJugadaOponente.y1;
    int x2 = ultimaJugadaOponente.x2;
    int y2 = ultimaJugadaOponente.y2;

    // Lista de posibles movimientos adyacentes
    int desplazamientos[4][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    for (int i = 0; i < 4; ++i) {
        int nx1 = x1 + desplazamientos[i][0];
        int ny1 = y1 + desplazamientos[i][1];
        int nx2 = x2 + desplazamientos[i][0];
        int ny2 = y2 + desplazamientos[i][1];

        // Verificar que las nuevas coordenadas están dentro de los límites y son válidas
        if (tablero->esMovimientoValido(nx1, ny1, nx2, ny2) && !juego->dejaCasillaDisponibleParaOponente(nx1, ny1, nx2, ny2)) {
            if (juego->hacerMovimiento(nx1, ny1, nx2, ny2)) {
                return;
            }
        }
    }

    // Si no se encontró un movimiento seguro, realizar un movimiento aleatorio seguro
    EstrategiaAleatoria* aleatorio = new EstrategiaAleatoria();
    aleatorio->realizarMovimientoAleatorioSeguro(juego);
}



