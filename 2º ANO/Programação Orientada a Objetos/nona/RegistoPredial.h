//
// Created by Utilizador on 30/11/2023.
//

#ifndef NONA_REGISTOPREDIAL_H
#define NONA_REGISTOPREDIAL_H

#include <vector>

#include "Imovel.h"

class RegistoPredial {
    vector<Imovel *> imoveis;
public:
    ~RegistoPredial();

    Imovel * pesquisa(const string &cod);

    bool acrescenta(Imovel *im);
};


#endif //NONA_REGISTOPREDIAL_H
