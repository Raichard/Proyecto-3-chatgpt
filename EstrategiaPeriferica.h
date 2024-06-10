#pragma once

#include "EstrategiaAleatoria.h"

class EstrategiaPeriferica : public Estrategia {
public:
    void realizarMovimiento(Juego* juego) override;
};
