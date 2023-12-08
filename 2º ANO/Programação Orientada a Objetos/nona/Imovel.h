//
// Created by Utilizador on 30/11/2023.
//

#ifndef NONA_IMOVEL_H
#define NONA_IMOVEL_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Imovel {
    float preco;
    int area, andar;
    string codigo, tipo;
    static int contador;
public:
    Imovel(float preco, int area, int andar, const string &tipo);
    ~Imovel();

    const string &getCodigo() const;
    float getPreco() const;
    int getAndar() const;

    virtual string getAsString() const;
};

ostream &operator<<(ostream &o, const Imovel &im); // SAI SEMPRE NO EXAME

#endif //NONA_IMOVEL_H
