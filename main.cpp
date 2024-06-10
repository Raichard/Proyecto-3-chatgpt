#include "Juego.h"
#include "Jugador.h"
#include "EstrategiaAleatoria.h"
#include "EstrategiaCercana.h"
#include "EstrategiaPeriferica.h"
#include "EstrategiaCentral.h"
#include "EstrategiaIslas.h"

int main() {
    Jugador jugador1(1, "Richi", true);
    Jugador jugador2(2, "Yuben", true);
    int fil = 3;
    int col = 3;

    // Definir un área irregular dinámicamente
    bool** area = new bool* [fil];
    for (int i = 0; i < fil; ++i) {
        area[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            area[i][j] = true;
        }
    }

    Juego* game = new Juego(fil, col, &jugador1, &jugador2, area);

    Estrategia* estrategia = new EstrategiaAleatoria(); // Ejemplo inicial
    game->cambiarEstrategia(estrategia);

    while (!game->esFinDelJuego()) {
        std::cout << game->obtenerTablero()->mostrar() << std::endl;

        std::cout << "Ultimo movimiento P1: " << jugador1.obtenerUltimaJugada().x1 << jugador1.obtenerUltimaJugada().y1 << jugador1.obtenerUltimaJugada().x2 << jugador1.obtenerUltimaJugada().y2 << std::endl;
        std::cout << "Ultimo movimiento IA: " << jugador2.obtenerUltimaJugada().x1 << jugador2.obtenerUltimaJugada().y1 << jugador2.obtenerUltimaJugada().x2 << jugador2.obtenerUltimaJugada().y2 << std::endl;

        if (game->obtenerJugadorActual() == &jugador1) {
            int x1, y1, x2, y2;
            std::cout << "Turno de " << game->obtenerJugadorActual()->getNombre() << "\n";
            std::cout << "Ingrese las coordenadas (x1 y1 x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;

            if (!game->hacerMovimiento(x1, y1, x2, y2)) {
                std::cout << "Movimiento inválido. Intente de nuevo.\n";
            }
        }
        else {
            std::cout << "Toca IA" << std::endl;
            game->realizarMovimientoAI();
        }
    }

    std::cout << game->obtenerTablero()->mostrar() << std::endl;
    Jugador* ganador = game->determinarGanador();
    if (ganador) {
        std::cout << "El ganador es " << ganador->getNombre() << " con " << ganador->getPuntuacionActual() << " puntos!\n";
    }
    else {
        std::cout << "El juego terminó en empate.\n";
    }

    // Liberar memoria del área
    for (int i = 0; i < fil; ++i) {
        delete[] area[i];
    }
    delete[] area;

    delete game;

    return 0;
}
