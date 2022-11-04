#ifndef AULA7_PONTO_H
#define AULA7_PONTO_H

#pragma once

#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

class ponto{
    int x, y;

public:
    ponto(int x = 0, int y = 0);
    ~ponto();

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    double distancia(ponto& p) const;

    string getAsString() const;
};

#endif //AULA7_PONTO_H
