#ifndef GUIAO3_PESSOA_H
#define GUIAO3_PESSOA_H

typedef struct pessoa no, *pno;

struct pessoa{
    char nome[100];
    int id;
    float peso, altura;
    pno prox;
};

pno adiciona(pno p);

void listarTudo(pno p);

void atualizaPeso(pno p, int id, float novoPeso);

pno elimina(pno p, int id);

#endif //GUIAO3_PESSOA_H
