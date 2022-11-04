#include <string>
#include <iostream>
#include <cmath>

#include "ponto.h"

using namespace std;

ponto::ponto(int x, int y) : x(x), y(y){
    cout << "... a contruir ponto" << getAsString() << "\n";
}

ponto::~ponto() {
    cout << "... a destruir ponto" << getAsString() << "\n";
}

double ponto::distancia(ponto& p) const{
    double dist;

    dist = sqrt(((this -> x - p.x) * (this -> x - p.x)) + (this -> y - p.y) * (this -> y - p.y));

    return dist;
}

int ponto::getX() const {
    return x;
}

int ponto::getY() const {
    return y;
}

void ponto::setX(int x) {
    x = x;
}

void ponto::setY(int y) {
    y = y;
}

string ponto::getAsString() const {
    ostringstream buffer0;
    buffer0 << " X: " << x << ", Y: " << y << "\n";
    return buffer0.str();
}