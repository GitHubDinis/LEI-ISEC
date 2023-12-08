#ifndef QUARTA1_AVISO_H
#define QUARTA1_AVISO_H

#include <iostream>

#include "Prego.h"

using namespace std;

class Aviso {
    string texto;
    Prego *p;
public:
    Aviso(string texto, Prego &p);
    ~Aviso();

    string getAsString() const;
};


#endif //QUARTA1_AVISO_H
