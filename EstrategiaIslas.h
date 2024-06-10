#pragma once

#include "EstrategiaAleatoria.h"

class EstrategiaIslas : public Estrategia {
public:
    void realizarMovimiento(Juego* juego) override;
};