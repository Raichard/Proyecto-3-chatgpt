#pragma once
#include "Juego.h"

using namespace std;

class Juego; // declaracion adelantada para evitar referencia circular

class Estrategia {
public:
    virtual ~Estrategia() = default;
    virtual void realizarMovimiento(Juego* juego) = 0;
};
