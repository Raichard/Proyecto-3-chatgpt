#pragma once

#include "Estrategia.h"

class EstrategiaAleatoria : public Estrategia {
public:
    EstrategiaAleatoria();

    void realizarMovimiento(Juego* juego) override;
    void realizarMovimientoAleatorioSeguro(Juego* juego);
};
