#include "Fracao.h"

// CONSTRUTOR

Fracao::Fracao(int a, int b) {
    numerador = a;
    if(b == 0){
        denominador = 1;
    } else{
        denominador = b;
    }
    cout << "Construtor de Fracao!\n";
}

// DESTRUTOR

Fracao::~Fracao() {
    cout << "Destrutor de Fracao!\n";
}

// GETTERS

int Fracao::getNum() const {
    return numerador;
}

int Fracao::getDen() const {
    return denominador;
}

// SETTERS

void Fracao::setNum(int n) {
    this->numerador = n;
}

void Fracao::setDen(int d) {
    this->denominador = d;
}

// OPERADORES

Fracao &Fracao::operator*=(const Fracao &o) {
    numerador *= o.numerador;
    denominador *= o.denominador;

    return *this;
}

Fracao &Fracao::operator++() {
    numerador += 1;
    return *this;
}

Fracao Fracao::operator++(int) {
    Fracao anterior(numerador, denominador);
    numerador += 1;
    return anterior;
}