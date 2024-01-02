#ifndef NEWWORKPOO_COMPONENTE_H
#define NEWWORKPOO_COMPONENTE_H

#include <iostream>
#include <sstream>

using namespace std;

class Componente {
public:
    Componente(char letra, string nome, string tipoOuComando);
    virtual ~Componente();

    string getTipo() const;
    int getIDnum() const;
    char getLetra() const;
    string getTipoOuComando() const;

    void setComando(string novoComando);

    virtual Componente* clone() const = 0;

    virtual string getAsString() const = 0;
private:
    char letra;
    string tipo, nome, tipoOuComando;
    int ID;
};


#endif //NEWWORKPOO_COMPONENTE_H
