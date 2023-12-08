#ifndef QUINTA_PESSOA_H
#define QUINTA_PESSOA_H

#include <iostream>
#include <sstream>

using namespace std;

class Pessoa {
    string nome;
    int bi, nif;
public:
    Pessoa(string nome, int bi, int nif);
    ~Pessoa();

    string getNome() const;
    int getBI() const;
    int getNIF() const;

    void setNome(string nome);
    void setBI(int bi);
    void setNIF(int nif);

    string getAsString() const;
};


#endif //QUINTA_PESSOA_H
