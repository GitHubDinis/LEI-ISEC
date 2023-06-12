#ifndef WORKP_LINHA_H
#define WORKP_LINHA_H

#include "utils.h"
#include "paragem.h"

typedef struct linha lna, *ln;

struct linha{
    char nome[99];
    pg lista;
    ln prox;
    int nParagens;
};

pg eliminaParagem(pg tab, int *n, ln linha);

ln adicionaLinha(ln tab, pg par, int *n);

void visualizaLinhas(ln tab);

ln atualizaLinha(ln tab, pg par, int *n);

ln adicionaLinhaFicheiro(ln tab, pg par, int *n);

void armazenaBinario(ln tab, pg par, int *n);

void calculaPercurso(ln tab, pg par, int *n);

void visualizaLinhasParagem(ln tab);

#endif //WORKP_LINHA_H
