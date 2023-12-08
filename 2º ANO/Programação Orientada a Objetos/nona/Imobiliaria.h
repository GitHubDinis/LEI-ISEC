//
// Created by Utilizador on 30/11/2023.
//

#ifndef NONA_IMOBILIARIA_H
#define NONA_IMOBILIARIA_H

#include <vector>
#include <iostream>

#include "Imovel.h"

using namespace std;

class Imobiliaria {
    vector <Imovel *> imoveis;
    string nome;

    int pesquisa(const string &codigo) const;
public:
    Imobiliaria(const string &nome);
    ~Imobiliaria();

    bool acrescenta(Imovel *i);
    string listaPorAndar(int andar);
    string listaPorCodigo(const string &codigo);

    bool removePorCodigo(const string &codigo);

    string getAsString() const;
};

#endif //NONA_IMOBILIARIA_H