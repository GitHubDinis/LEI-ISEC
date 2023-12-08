#ifndef QUARTA_PONTO_H
#define QUARTA_PONTO_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

static int counter = 0;

class Ponto {
    int x, y;
    int id;
public:
    Ponto(int x = 0, int y = 0);
    ~Ponto();

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    string getAsString() const;

    void distancia(Ponto p1);
};


#endif //QUARTA_PONTO_H
