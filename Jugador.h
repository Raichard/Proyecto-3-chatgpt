#pragma once
#include <iostream>
#include "Movimiento.h"
using namespace std;

class Jugador {
private:
    int id;
    string nombre;
    int puntuacionActual;
    int puntuacionMasAlta;
    bool humano;
    Movimiento ultimaJugada;

public:
    Jugador(int id, const string& nombre, bool esHumano);

    int getId() const;
    string getNombre() const;
    int getPuntuacionActual() const;
    int getPuntuacionMasAlta() const;
    bool esHumano() const;

    void setPuntuacionActual(int puntuacion);
    void setPuntuacionMasAlta(int puntuacion);
    void incrementarPuntuacion(int puntos);

    Movimiento obtenerUltimaJugada() const;
    void setUltimaJugada(int x1, int y1, int x2, int y2);
};
