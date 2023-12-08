#ifndef QUARTA1_PREGO_H
#define QUARTA1_PREGO_H

#include <iostream>
#include <sstream>

using namespace std;

class Prego {
    int x, y;
public:
    Prego(int a, int b);
    ~Prego();

    void mudaDeSitio(int a, int b);
    string getAsString() const;
};


#endif //QUARTA1_PREGO_H
