#include "Tablero.h"

Tablero::Tablero(int fil, int col){
    filas = fil;
    columnas = col;
    // Asignar memoria para la matriz de punteros a punteros a char
    board = new char** [filas * 2 - 1];
    for (int i = 0; i < filas * 2 - 1; ++i) {
        board[i] = new char* [columnas * 2 - 1];
        for (int j = 0; j < columnas * 2 - 1; ++j) {
            board[i][j] = new char(' ');
        }
    }

    // Asignar memoria para la matriz de bool
    area = new bool* [filas];
    for (int i = 0; i < filas; ++i) {
        area[i] = new bool[columnas];
        for (int j = 0; j < columnas; ++j) {
            area[i][j] = false;
        }
    }
}

Tablero::~Tablero() {
    // Liberar memoria de la matriz de punteros a punteros a char
    for (int i = 0; i < filas * 2 - 1; ++i) {
        for (int j = 0; j < columnas * 2 - 1; ++j) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;

    // Liberar memoria de la matriz de bool
    for (int i = 0; i < filas; ++i) {
        delete[] area[i];
    }
    delete[] area;
}

void Tablero::configurarAreaIrregular(bool** area) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            this->area[i][j] = area[i][j];
            if (area[i][j]) {
                *board[i * 2][j * 2] = '+';
            }
        }
    }
}

string Tablero::mostrar() {
    stringstream s;
    for (int i = 0; i < filas * 2 - 1; ++i) {
        for (int j = 0; j < columnas * 2 - 1; ++j) {
            s << *board[i][j] << ' ';
        }
        s << '\n';
    }
    return s.str();
}

bool Tablero::agregarLinea(int x1, int y1, int x2, int y2) {
    if ((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2 && std::abs(x1 - x2) == 1)) {
        // Verificar si los puntos están dentro del área permitida
        if (!area[x1][y1] || !area[x2][y2]) {
            return false;
        }

        int fila = x1 + x2;
        int columna = y1 + y2;

        // Verificar si fila y columna están dentro de los límites del tablero
        if (fila >= 0 && fila < 2 * getFilas() - 1 && columna >= 0 && columna < 2 * getColumnas() - 1) {
            if (*board[fila][columna] == ' ') {
                if (x1 == x2) {
                    *board[fila][columna] = '-'; // Línea horizontal
                }
                else if (y1 == y2) {
                    *board[fila][columna] = '|'; // Línea vertical
                }
                return true;
            }
        }
    }
    return false;
}

char* Tablero::getCelda(int fila, int columna) const {
    return board[fila][columna];
}

int Tablero::getFilas() const {
    return filas;
}

int Tablero::getColumnas() const {
    return columnas;
}

bool Tablero::esAreaValida(int fila, int columna) {
    return area[fila][columna];
}

char*** Tablero::obtenerBoard() const {
    return board;
}

bool Tablero::esMovimientoValido(int x1, int y1, int x2, int y2) {
    if ((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2 && std::abs(x1 - x2) == 1)) {
        if (x1 >= 0 && x1 < getFilas() && y1 >= 0 && y1 < getColumnas() &&
            x2 >= 0 && x2 < getFilas() && y2 >= 0 && y2 < getColumnas()) {
            int fila = x1 + x2;
            int columna = y1 + y2;
            return (*board[fila][columna] == ' ');
        }
    }
    return false;
}

bool Tablero::dejaCasillaCompleta(int x, int y) {
    bool completa = false;

    // Superior izquierda
    if (x > 0 && y > 0) {
        completa |= (*board[2 * (x - 1) + 1][2 * (y - 1) + 1] == '-' &&
            *board[2 * (x - 1) + 1][2 * y + 1] == '|' &&
            *board[2 * x + 1][2 * (y - 1) + 1] == '|' &&
            *board[2 * x + 1][2 * y + 1] == '-');
    }
    // Superior derecha
    if (x > 0 && y < getColumnas() - 1) {
        completa |= (*board[2 * (x - 1) + 1][2 * y + 1] == '-' &&
            *board[2 * (x - 1) + 1][2 * (y + 1) + 1] == '|' &&
            *board[2 * x + 1][2 * y + 1] == '|' &&
            *board[2 * x + 1][2 * (y + 1) + 1] == '-');
    }
    // Inferior izquierda
    if (x < getFilas() - 1 && y > 0) {
        completa |= (*board[2 * x + 1][2 * (y - 1) + 1] == '-' &&
            *board[2 * x + 1][2 * y + 1] == '|' &&
            *board[2 * (x + 1) + 1][2 * (y - 1) + 1] == '|' &&
            *board[2 * (x + 1) + 1][2 * y + 1] == '-');
    }
    // Inferior derecha
    if (x < getFilas() - 1 && y < getColumnas() - 1) {
        completa |= (*board[2 * x + 1][2 * y + 1] == '-' &&
            *board[2 * x + 1][2 * (y + 1) + 1] == '|' &&
            *board[2 * (x + 1) + 1][2 * y + 1] == '|' &&
            *board[2 * (x + 1) + 1][2 * (y + 1) + 1] == '-');
    }

    return completa;
}

bool Tablero::dejaCasillaCasiCompleta(int x, int y) {
    bool casiCompleta = false;

    // Verificar las cuatro posibles casillas que pueden contener el punto (x, y)

    // Superior izquierda
    if (x > 0 && y > 0) {
        int conteo = 0;
        if (2 * (x - 1) + 1 < filas * 2 - 1 && 2 * (y - 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x - 1) + 1][2 * (y - 1) + 1] != ' ') ? 1 : 0;
        if (2 * (x - 1) + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x - 1) + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * (y - 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * (y - 1) + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * y + 1] != ' ') ? 1 : 0;
        casiCompleta |= (conteo == 3);
    }

    // Superior derecha
    if (x > 0 && y < columnas - 1) {
        int conteo = 0;
        if (2 * (x - 1) + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x - 1) + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * (x - 1) + 1 < filas * 2 - 1 && 2 * (y + 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x - 1) + 1][2 * (y + 1) + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * (y + 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * (y + 1) + 1] != ' ') ? 1 : 0;
        casiCompleta |= (conteo == 3);
    }

    // Inferior izquierda
    if (x < filas - 1 && y > 0) {
        int conteo = 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * (y - 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * (y - 1) + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * (x + 1) + 1 < filas * 2 - 1 && 2 * (y - 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x + 1) + 1][2 * (y - 1) + 1] != ' ') ? 1 : 0;
        if (2 * (x + 1) + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x + 1) + 1][2 * y + 1] != ' ') ? 1 : 0;
        casiCompleta |= (conteo == 3);
    }

    // Inferior derecha
    if (x < filas - 1 && y < columnas - 1) {
        int conteo = 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * x + 1 < filas * 2 - 1 && 2 * (y + 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * x + 1][2 * (y + 1) + 1] != ' ') ? 1 : 0;
        if (2 * (x + 1) + 1 < filas * 2 - 1 && 2 * y + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x + 1) + 1][2 * y + 1] != ' ') ? 1 : 0;
        if (2 * (x + 1) + 1 < filas * 2 - 1 && 2 * (y + 1) + 1 < columnas * 2 - 1)
            conteo += (*board[2 * (x + 1) + 1][2 * (y + 1) + 1] != ' ') ? 1 : 0;
        casiCompleta |= (conteo == 3);
    }

    return casiCompleta;
}

void Tablero::removerLinea(int x1, int y1, int x2, int y2) {
    if ((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2 && std::abs(x1 - x2) == 1)) {
        int fila = x1 + x2;
        int columna = y1 + y2;
        *board[fila][columna] = ' ';
    }
}

bool Tablero::lineaExiste(int x1, int y1, int x2, int y2) {
    int fila = x1 + x2;
    int columna = y1 + y2;
    return *board[fila][columna] != ' ';
}