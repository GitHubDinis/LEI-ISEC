#ifndef SEXTA_FRACAO_H
#define SEXTA_FRACAO_H

#include <iostream>

using namespace std;

class Fracao {
    int numerador, denominador;
public:
    Fracao(int a, int b = 1);
    ~Fracao();

    int getNum() const;
    int getDen() const;
    void setNum(int n);
    void setDen(int d);

    Fracao &operator*=(const Fracao &o);
    Fracao &operator++();
    Fracao operator++(int);
};

Fracao operator*(const Fracao &a, const Fracao &b){
    return Fracao(a.getNum()*b.getNum(), a.getDen()*b.getDen());
};

ostream &operator<<(ostream &o, const Fracao &f){
    o << f.getNum();
    o << '/';
    o << f.getDen();
    return o;
};


#endif //SEXTA_FRACAO_H
