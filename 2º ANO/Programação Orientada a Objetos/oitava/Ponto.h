#ifndef OITAVA_PONTO_H
#define OITAVA_PONTO_H

#include <iostream>

using namespace std;

class Ponto {
public:
    Ponto (int cx = 0, int cy = 0);
    ~Ponto();
private:
    int x, y;
};


#endif //OITAVA_PONTO_H
