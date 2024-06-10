#include "Juego.h"
#include "Estrategia.h"

Juego::Juego(int filas, int columnas, Jugador* j1, Jugador* j2, bool** area) {
    tablero = new Tablero(filas, columnas);
    tablero->configurarAreaIrregular(area);
    jugador1 = j1;
    jugador2 = j2;
    jugadorActual = jugador1;
    estrategia = nullptr; // Inicialmente sin estrategia
}

Juego::~Juego() {
    delete tablero;
    delete estrategia; // Aseguramos liberar la estrategia
}

void Juego::cambiarTurno() {
    if (jugadorActual == jugador1)
        jugadorActual = jugador2;
    else
        jugadorActual = jugador1;
}

bool Juego::esMovimientoValido(int x1, int y1, int x2, int y2) {
    if ((x1 == x2 && abs(y1 - y2) == 1) || (y1 == y2 && abs(x1 - x2) == 1)) {
        return tablero->esAreaValida(x1, y1) && tablero->esAreaValida(x2, y2) && !tablero->lineaExiste(x1, y1, x2, y2);
    }
    return false;
}

void Juego::iniciarJuego() {
    // placeholder
}

bool Juego::hacerMovimiento(int x1, int y1, int x2, int y2) {
    if (esMovimientoValido(x1, y1, x2, y2)) {
        if (tablero->agregarLinea(x1, y1, x2, y2)) {
            // Verificar si se ha formado un cuadrado
            jugadorActual->setUltimaJugada(x1, y1, x2, y2);
            if (verificarCuadrados(x1, y1, x2, y2)) {
                // Si se formó un cuadrado, no cambiar el turno
                return true;
            }
            else {
                // Si no se formó un cuadrado, cambiar el turno
                cambiarTurno();
                return true;
            }
        }
    }
    return false;
}

bool Juego::verificarCuadrados(int x1, int y1, int x2, int y2) {
    bool seFormoCuadrado = false;

    // Verificar todas las posiciones alrededor de la línea agregada
    for (int dx = -1; dx <= 0; ++dx) {
        for (int dy = -1; dy <= 0; ++dy) {
            int nx = x1 + dx;
            int ny = y1 + dy;
            if (nx >= 0 && ny >= 0 && nx < tablero->getFilas() - 1 && ny < tablero->getColumnas() - 1 && esCuadradoCompleto(nx, ny)) {
                // Si se formó un cuadrado, actualizar el tablero y la puntuación
                int centroX = nx * 2 + 1;
                int centroY = ny * 2 + 1;
                if (*tablero->obtenerBoard()[centroX][centroY] == ' ') {
                    *tablero->obtenerBoard()[centroX][centroY] = jugadorActual->getNombre()[0];
                    jugadorActual->incrementarPuntuacion(1);
                    seFormoCuadrado = true;
                }
            }
        }
    }

    return seFormoCuadrado;
}


bool Juego::esCuadradoCompleto(int x, int y) {
    if (x < 0 || y < 0 || x >= tablero->getFilas() - 1 || y >= tablero->getColumnas() - 1) {
        return false;
    }
    return *tablero->obtenerBoard()[x * 2][y * 2] == '+' &&
        *tablero->obtenerBoard()[x * 2][(y * 2) + 2] == '+' &&
        *tablero->obtenerBoard()[(x * 2) + 2][y * 2] == '+' &&
        *tablero->obtenerBoard()[(x * 2) + 2][(y * 2) + 2] == '+' &&
        *tablero->obtenerBoard()[x * 2][(y * 2) + 1] != ' ' &&
        *tablero->obtenerBoard()[(x * 2) + 1][y * 2] != ' ' &&
        *tablero->obtenerBoard()[(x * 2) + 1][(y * 2) + 2] != ' ' &&
        *tablero->obtenerBoard()[(x * 2) + 2][(y * 2) + 1] != ' ';
}


Tablero* Juego::obtenerTablero() const {
    return tablero;
}

Jugador* Juego::obtenerJugadorActual() const {
    return jugadorActual;
}

Jugador* Juego::obtenerJugador1() const {
    return jugador1;
}

Jugador* Juego::obtenerJugador2() const {
    return jugador2;
}


bool Juego::esFinDelJuego() const {
    for (int i = 0; i < tablero->getFilas() * 2 - 1; ++i) {
        for (int j = 0; j < tablero->getColumnas() * 2 - 1; ++j) {
            if (*tablero->obtenerBoard()[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

Jugador* Juego::determinarGanador() const {
    if (jugador1->getPuntuacionActual() > jugador2->getPuntuacionActual()) {
        return jugador1;
    }
    else if (jugador2->getPuntuacionActual() > jugador1->getPuntuacionActual()) {
        return jugador2;
    }
    else {
        return nullptr; // Empate
    }
}


void Juego::cambiarEstrategia(Estrategia* nuevaEstrategia) {
    estrategia = nuevaEstrategia;
}

void Juego::realizarMovimientoAI() {
    estrategia->realizarMovimiento(this);
}

bool Juego::dejaCasillaDisponibleParaOponente(int x1, int y1, int x2, int y2) {
    Tablero* tablero = obtenerTablero();

    // Simular el movimiento
    tablero->agregarLinea(x1, y1, x2, y2);

    // Verificar si alguna casilla alrededor de (x1, y1) o (x2, y2) queda a un movimiento de completarse
    bool resultado = false;

    // Verificar las casillas alrededor de (x1, y1)
    resultado |= tablero->dejaCasillaCasiCompleta(x1, y1);
    // Verificar las casillas alrededor de (x2, y2)
    resultado |= tablero->dejaCasillaCasiCompleta(x2, y2);

    // Revertir el movimiento simulado
    tablero->removerLinea(x1, y1, x2, y2);

    return resultado;
}


bool Juego::dejaCasillaDisponibleParaJugador(int x1, int y1, int x2, int y2) {
    Tablero* tablero = obtenerTablero();

    // Simular el movimiento
    if (!tablero->agregarLinea(x1, y1, x2, y2)) {
        std::cout << "No se pudo agregar la línea para (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ")\n";
        return false;
    }

    std::cout << "Simulando movimiento: (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << ")\n";

    // Verificar si alguna casilla alrededor de (x1, y1) o (x2, y2) queda completa
    bool resultado_x1y1 = tablero->dejaCasillaCompleta(x1, y1);
    bool resultado_x2y2 = tablero->dejaCasillaCompleta(x2, y2);
    bool resultado = resultado_x1y1 || resultado_x2y2;

    // Imprimir resultados intermedios
    std::cout << "Resultado de dejaCasillaCompleta para (" << x1 << ", " << y1 << "): " << resultado_x1y1 << "\n";
    std::cout << "Resultado de dejaCasillaCompleta para (" << x2 << ", " << y2 << "): " << resultado_x2y2 << "\n";

    // Revertir el movimiento simulado
    tablero->removerLinea(x1, y1, x2, y2);

    std::cout << "Resultado de dejaCasillaDisponibleParaJugador: " << resultado << "\n";

    return resultado;
}
