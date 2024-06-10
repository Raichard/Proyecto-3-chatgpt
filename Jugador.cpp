#include "Jugador.h"

Jugador::Jugador(int ident, const string& nom, bool hum) : ultimaJugada(0, 0, 0, 0) {
    id = ident;
    nombre = nom;
    humano = hum;
}

int Jugador::getId() const {
    return id;
}

string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntuacionActual() const {
    return puntuacionActual;
}

int Jugador::getPuntuacionMasAlta() const {
    return puntuacionMasAlta;
}

bool Jugador::esHumano() const {
    return humano;
}

void Jugador::setPuntuacionActual(int puntuacion) {
    puntuacionActual = puntuacion;
    if (puntuacionActual > puntuacionMasAlta) {
        puntuacionMasAlta = puntuacionActual;
    }
}

void Jugador::setPuntuacionMasAlta(int puntuacion) {
    puntuacionMasAlta = puntuacion;
}

void Jugador::incrementarPuntuacion(int puntos) {
    puntuacionActual += puntos;
    if (puntuacionActual > puntuacionMasAlta) {
        puntuacionMasAlta = puntuacionActual;
    }
}

Movimiento Jugador::obtenerUltimaJugada() const {
    return ultimaJugada;
}

void Jugador::setUltimaJugada(int x1, int y1, int x2, int y2) {
    ultimaJugada = Movimiento(x1, y1, x2, y2);
}