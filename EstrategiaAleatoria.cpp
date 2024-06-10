#include "EstrategiaAleatoria.h"

EstrategiaAleatoria::EstrategiaAleatoria() {
    srand(time(NULL)); // Inicializar la semilla para números aleatorios
}

void EstrategiaAleatoria::realizarMovimiento(Juego* juego) {
    Tablero* tablero = juego->obtenerTablero();
    int filas = tablero->getFilas();
    int columnas = tablero->getColumnas();
    bool movimientoRealizado = false;
    int intentosMaximos = 400; // Limitar el número de intentos para evitar un bucle infinito
    int i = 0;
    // Primer intento: Completar cualquier casilla si es posible
    for (i; i < intentosMaximos; ++i) {
        int x1 = rand() % filas;
        int y1 = rand() % columnas;

        // Generar un movimiento aleatorio en una dirección válida
        int dir = rand() % 4;
        int x2 = x1, y2 = y1;

        switch (dir) {
        case 0: // Arriba
            x2 = x1 - 1;
            break;
        case 1: // Abajo
            x2 = x1 + 1;
            break;
        case 2: // Izquierda
            y2 = y1 - 1;
            break;
        case 3: // Derecha
            y2 = y1 + 1;
            break;
        }

        // Verificar que las coordenadas estén dentro de los límites del tablero
        if (x2 >= 0 && x2 < filas && y2 >= 0 && y2 < columnas) {
            if (juego->esMovimientoValido(x1, y1, x2, y2)) {
                if (juego->dejaCasillaDisponibleParaJugador(x1, y1, x2, y2)) {
                    // Movimiento que completa una casilla
                    if (juego->hacerMovimiento(x1, y1, x2, y2)) {
                        movimientoRealizado = true;
                        break;
                    }
                }
            }
        }
    }
    
    if (!movimientoRealizado)
    {
        cout << "no se encontro casilla ganada al: " << i << " intento" << endl;
    }

    i = 0;
    
    // Segundo intento: Movimientos seguros
    if (!movimientoRealizado && i < intentosMaximos) {
        for (int i = 0; i < intentosMaximos; ++i) {
            int x1 = rand() % filas;
            int y1 = rand() % columnas;

            // Generar un movimiento aleatorio en una dirección válida
            int dir = rand() % 4;
            int x2 = x1, y2 = y1;

            switch (dir) {
            case 0: // Arriba
                x2 = x1 - 1;
                break;
            case 1: // Abajo
                x2 = x1 + 1;
                break;
            case 2: // Izquierda
                y2 = y1 - 1;
                break;
            case 3: // Derecha
                y2 = y1 + 1;
                break;
            }

            // Verificar que las coordenadas estén dentro de los límites del tablero
            if (x2 >= 0 && x2 < filas && y2 >= 0 && y2 < columnas) {
                std::cout << "Verificando movimiento (" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 << "): ";
                if (juego->esMovimientoValido(x1, y1, x2, y2) &&
                    !juego->dejaCasillaDisponibleParaOponente(x1, y1, x2, y2)) {
                    std::cout << "movimiento seguro\n";
                    if (juego->hacerMovimiento(x1, y1, x2, y2)) {
                        movimientoRealizado = true;
                        break;
                    }
                }
                else {
                    std::cout << "movimiento no seguro\n";
                }
            }
        }
        ++i;
    }

    if (!movimientoRealizado)
    {
        cout << "no se encontro casilla segura al: " << i << " intento" << endl;
    }

    i = 0;

    // Tercer intento: Cualquier movimiento válido si no se encuentra un movimiento seguro
    if (!movimientoRealizado && i < intentosMaximos) {
        std::cout << "No se encontró un movimiento seguro, realizando cualquier movimiento válido\n";
        while (true) {
            int x1 = rand() % filas;
            int y1 = rand() % columnas;

            // Generar un movimiento aleatorio en una dirección válida
            int dir = rand() % 4;
            int x2 = x1, y2 = y1;

            switch (dir) {
            case 0: // Arriba
                x2 = x1 - 1;
                break;
            case 1: // Abajo
                x2 = x1 + 1;
                break;
            case 2: // Izquierda
                y2 = y1 - 1;
                break;
            case 3: // Derecha
                y2 = y1 + 1;
                break;
            }

            // Verificar que las coordenadas estén dentro de los límites del tablero
            if (x2 >= 0 && x2 < filas && y2 >= 0 && y2 < columnas) {
                if (juego->esMovimientoValido(x1, y1, x2, y2)) {
                    if (juego->hacerMovimiento(x1, y1, x2, y2)) {
                        return; // Salir del método una vez que se realiza un movimiento
                    }
                }
            }
        }
        ++i;
    }
}

void EstrategiaAleatoria::realizarMovimientoAleatorioSeguro(Juego* juego) {
    realizarMovimiento(juego);
}
