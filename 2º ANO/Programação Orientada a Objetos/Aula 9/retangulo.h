#ifndef UNTITLED20_RETANGULO_H
#define UNTITLED20_RETANGULO_H

#include <stdio.h>
#include "ponto.h"

class retangulo {
    ponto cse; //canto superior esquerdo
    double altura, largura;

public:
    retangulo(const ponto &p, double alt, double lar);
    retangulo(const retangulo &r);
    ~retangulo();

    string getAsString() const;

    double area() const;

    void setCanto(const ponto &nc);
};

#endif //UNTITLED20_RETANGULO_H
