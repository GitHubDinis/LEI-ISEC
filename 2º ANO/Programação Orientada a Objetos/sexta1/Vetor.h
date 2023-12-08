#ifndef SEXTA1_VETOR_H
#define SEXTA1_VETOR_H

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Vetor {
    double x, y;
public:
    Vetor(double x = 0, double y = 0);
    ~Vetor();

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    string getAsString() const;

    Vetor &operator+(const Vetor &v);
    Vetor &operator-(const Vetor &v);
    Vetor &operator+=(const Vetor &v);
    bool operator==(const Vetor &v);
    bool operator!=(const Vetor &v);

    // ALÍNEA D)
    operator double() const;
    Vetor &operator++();
    Vetor operator++(int);
};

inline ostream &operator<<(ostream &o, const Vetor &v){
    o << v.getX();
    o << " , ";
    o << v.getY();
    return o;
}

inline istream &operator>>(istream &is, Vetor &v){
    double x, y;
    cout << "X:";
    is >> x;
    v.setX(x);
    cout << "Y:";
    is >> y;
    v.setY(y);
    return is;
}

#endif //SEXTA1_VETOR_H
