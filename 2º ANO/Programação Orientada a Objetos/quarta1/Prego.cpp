#include "Prego.h"

// CONSTRUTOR

Prego::Prego(int a, int b) {
    x = a; y = b;
    cout << "Construindo prego em " << x << "," << y << "\n";
}

// DESTRUTOR

Prego::~Prego() {
    cout << "Destruindo prego em " << x << "," << y << "\n";
}

// IMPRIMIR

string Prego::getAsString() const {
    ostringstream buffer0;
    buffer0 << " X: " << x << ", Y: " << y << endl;
    return buffer0.str();
}

// MÉTODOS / FUNCIONALIDADES

void Prego::mudaDeSitio(int a, int b) {
    x = a; y = b;
}