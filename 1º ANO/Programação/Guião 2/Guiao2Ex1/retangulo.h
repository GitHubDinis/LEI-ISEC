#ifndef GUIAO2EXR1_RETANGULO_H
#define GUIAO2EXR1_RETANGULO_H

#include "ponto.h"

typedef struct retangulo ret2D;

struct retangulo{
    ponto2D cie;
    int larg, alt;
};

void printR(ret2D r1);

void initR(ret2D* p);

int areaR(ret2D r1);

int verificaR(ret2D r1, ponto2D p);

void deslocaR(ret2D r1, int dx, int dy);

#endif //GUIAO2EXR1_RETANGULO_H
