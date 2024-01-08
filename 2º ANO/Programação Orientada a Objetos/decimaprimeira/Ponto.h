//
// Created by Utilizador on 21/12/2023.
//

#ifndef DECIMAPRIMEIRA_PONTO_H
#define DECIMAPRIMEIRA_PONTO_H

#include <iostream>

using namespace std;

class Ponto {
public:
    Ponto(int cx = 0, int cy = 0);
    ~Ponto();
    void mostra() const;
private:
    int x,y;

};


#endif //DECIMAPRIMEIRA_PONTO_H
