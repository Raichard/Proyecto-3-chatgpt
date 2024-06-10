#pragma once

#include "EstrategiaAleatoria.h"

class EstrategiaCercana : public Estrategia {
public:
    void realizarMovimiento(Juego* juego) override;
};
