#pragma once
#include "Tablero.h"
#include "Jugador.h"
#include <cmath>

class Estrategia;

class Juego {
private:
    Tablero* tablero;
    Jugador* jugador1;
    Jugador* jugador2;
    Jugador* jugadorActual;
    Estrategia* estrategia;

public:
    Juego(int filas, int columnas, Jugador* j1, Jugador* j2, bool** area);
    ~Juego();

    void iniciarJuego(); //placeholder
    bool hacerMovimiento(int x1, int y1, int x2, int y2);
    bool verificarCuadrados(int x1, int y1, int x2, int y2);
    bool esCuadradoCompleto(int x, int y);

    Tablero* obtenerTablero() const;
    Jugador* obtenerJugadorActual() const;
    Jugador* obtenerJugador1() const;
    Jugador* obtenerJugador2() const;

    void cambiarTurno();
    bool esMovimientoValido(int x1, int y1, int x2, int y2);

    bool esFinDelJuego() const;
    Jugador* determinarGanador() const;


    void cambiarEstrategia(Estrategia* nuevaEstrategia);
    void realizarMovimientoAI();
    bool dejaCasillaDisponibleParaOponente(int x1, int y1, int x2, int y2);
    bool dejaCasillaDisponibleParaJugador(int x1, int y1, int x2, int y2);

};
