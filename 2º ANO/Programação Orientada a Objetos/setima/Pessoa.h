#ifndef SETIMA_PESSOA_H
#define SETIMA_PESSOA_H

#include <iostream>
#include <sstream>

using namespace std;

class Pessoa {
public:
    Pessoa(string nome, int bi, int nif);
    Pessoa();
    string getNome() const;
    int getBI() const;
    int getNIF() const;
    void setNome(string nome);
    string getAsString() const;
private:
    string nome;
    int bi, nif;
};


#endif //SETIMA_PESSOA_H
