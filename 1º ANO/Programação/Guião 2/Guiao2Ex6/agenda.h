#ifndef GUIAO2EX6_AGENDA_H
#define GUIAO2EX6_AGENDA_H

// ALÍNEA A)

typedef struct dados ct, *pct;

struct dados{
    int num;
    char nome[100];
};

pct addC(pct tab, int *n);
void listaC(ct *tab, int n);
int mostraNum(pct tab, char *nome, int n);
void atualizaNum(ct *tab, char *nome,int n);
pct eliminaC(pct tab, char *nome, int *n);

#endif //GUIAO2EX6_AGENDA_H
