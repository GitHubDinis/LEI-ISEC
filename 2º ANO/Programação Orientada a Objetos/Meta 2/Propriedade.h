#ifndef NEWWORKPOO_PROPRIEDADE_H
#define NEWWORKPOO_PROPRIEDADE_H

#include <iostream>
#include <sstream>

using namespace std;

class Propriedade {
public:
    Propriedade(string nome, float valor);
    virtual ~Propriedade();

    string getNome() const;
    float getValor() const;

    void setValor(float novoValor);

    string getAsString() const;
private:
    string nome; // Nome da propriedade
    float valor;
};


#endif //NEWWORKPOO_PROPRIEDADE_H
