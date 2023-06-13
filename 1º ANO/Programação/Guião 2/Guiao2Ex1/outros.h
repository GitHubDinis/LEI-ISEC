#ifndef GUIAO2EXR1_OUTROS_H
#define GUIAO2EXR1_OUTROS_H

#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"

int addR(struct retangulo a[], int *p);

void listaTodos(struct retangulo a[], int tam);

void listaQuadrados(struct retangulo a[], int tam);

int eliminaPequeno(struct retangulo a[], int *p);

int eliminaInferior(struct retangulo a[], int *p, int lim);

void ordenaRet(struct retangulo a[], int tam);

#endif //GUIAO2EXR1_OUTROS_H
