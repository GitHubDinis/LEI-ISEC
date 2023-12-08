#include "Triangulo.h"

// CONSTRUTOR

Triangulo::Triangulo(string nome, Ponto a, Ponto b, Ponto c) : nome(nome), a(a), b(b), c(c){
    this->nome = nome;
    cout << "Construtor de Triangulo!" << endl;
}

// DESTRUTOR

Triangulo::~Triangulo() {
    cout << "Destrutor de Triangulo!" << endl;
}

// GETTERS

string Triangulo::getNome() const {
    return nome;
}

// SETTERS

void Triangulo::setNome(string nome) {
    nome = nome;
}

// IMPRIMIR INFORMAÇÃO

string Triangulo::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Nome: " << nome << " Ponto 1: (" << a.getX() << "," << a.getY() << ")" << " Ponto 2: (" << b.getX() << "," << b.getY() << ")" << " Ponto 3: (" << c.getX() << "," << c.getY() << ")" << endl;
    return buffer0.str();
}