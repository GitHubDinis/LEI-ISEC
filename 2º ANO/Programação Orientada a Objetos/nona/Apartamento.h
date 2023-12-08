//
// Created by Utilizador on 30/11/2023.
//

#ifndef NONA_APARTAMENTO_H
#define NONA_APARTAMENTO_H

#include "Imovel.h"

class Apartamento : public Imovel {
    int n_assoal;
public:
    Apartamento(int area, int andar, int n_assoal);
    ~Apartamento();

    int getNAssoal() const;

    string getAsString() const;
};


#endif //NONA_APARTAMENTO_H
