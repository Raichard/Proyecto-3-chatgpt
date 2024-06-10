#pragma once

#include "EstrategiaAleatoria.h"

class EstrategiaCentral : public Estrategia {
public:
    void realizarMovimiento(Juego* juego) override;
};
