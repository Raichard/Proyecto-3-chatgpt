
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

#pragma once

class Tablero {
private:
    int filas;
    int columnas;
    bool** area; // Matriz de punteros a punteros a bool
    char*** board; // Matriz de punteros a punteros a char

public:
    Tablero(int filas, int columnas);
    ~Tablero(); // Destructor para liberar memoria
    void configurarAreaIrregular(bool** area);
    string mostrar();
    bool agregarLinea(int x1, int y1, int x2, int y2);
    char* getCelda(int fila, int columna) const;
    int getFilas() const;
    int getColumnas() const;
    bool esAreaValida(int fila, int columna);
    char*** obtenerBoard() const;

    bool esMovimientoValido(int x1, int y1, int x2, int y2);
    bool dejaCasillaCompleta(int x1, int y1);
    void removerLinea(int x1, int y1, int x2, int y2);
    bool lineaExiste(int x1, int y1, int x2, int y2);
    bool dejaCasillaCasiCompleta(int x, int y);

    // Se necesitan otros metodos?
};