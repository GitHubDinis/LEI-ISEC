#include "Ponto.h"

Ponto::Ponto(int cx, int cy) : x(cx), y(cy) {
    cout << "CONSTR. Ponto com " << x << "," << y << "\n";
}
Ponto::~Ponto(){
    cout << "DESTR. Ponto com " << x << "," << y << "\n";
}

