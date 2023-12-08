#ifndef QUARTA_TRIANGULO_H
#define QUARTA_TRIANGULO_H

#include "Ponto.h"

using namespace std;

class Triangulo {
    Ponto a, b, c;
    string nome;
public:
    Triangulo(string nome, Ponto a, Ponto b, Ponto c);
    ~Triangulo();

    string getNome() const;
    void setNome(string nome);

    string getAsString() const;
};


#endif //QUARTA_TRIANGULO_H
