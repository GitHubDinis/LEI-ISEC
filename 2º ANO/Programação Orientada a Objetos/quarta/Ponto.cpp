#include "Ponto.h"

// CONTRUTOR

Ponto::Ponto(int x, int y) : x(x), y(y){
    cout << "Contrutor de um Ponto!" << endl;
    counter++;
    id = counter;
}

// DESTRUTOR

Ponto::~Ponto() {
    cout << "Destrutor de um Ponto!" << endl;
}

// GETTERS

int Ponto::getX() const {
    return x;
}

int Ponto::getY() const {
    return y;
}

// SETTERS

void Ponto::setX(int x) {
    this->x = x;
}

void Ponto::setY(int y) {
    this->y = y;
}

// IMPRIMIR INFORMAÇÃO

string Ponto::getAsString() const {
    ostringstream buffer0;
    buffer0 << " X: " << x << ", Y: " << y << ", ID: " << id << "\n";
    return buffer0.str();
}

// MÉTODOS / FUNCIONALIDADES

void Ponto::distancia(Ponto p1) {
    cout << "Distance: " << sqrt(((p1.x-this->x)*(p1.x-this->x))+((p1.y-this->y)*(p1.y-this->y))) << endl;
}

