#ifndef WORKP_PARAGEM_H
#define WORKP_PARAGEM_H

#include "utils.h"

typedef struct paragem pgm, *pg;

struct paragem{
    char codigo_alfanumerico[5];
    char nome[99];
};

pg adicionaParagem(pg tab, int *n);

void visualizaParagens(pg tab, int n);

pg paragemExiste(pg tab, int *n, char *nomeParagem);

void adicionaCodigoParagem(char *codigo, int tamanho);

pg adicionaParagensFicheiro(pg tab, int *n);

void visualizaParagensFicheiro(pg tab, int n);

#endif //WORKP_PARAGEM_H
