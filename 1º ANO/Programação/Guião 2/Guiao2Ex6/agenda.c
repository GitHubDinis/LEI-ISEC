#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALÍNEA C)

pct addC(pct tab, int *n){
    pct p;

    char nome[15];
    int numero;

    printf("Nome do contacto: ");
    scanf("%s", nome);

    printf("Numero do contacto: ");
    scanf("%d", &numero);

    p = realloc(tab, sizeof(ct)*(*n + 1));

    if(p != NULL){
        tab = p;
        strcpy(tab[*n].nome, nome);
        tab[*n].num = numero;
        (*n)++;
    }
    return tab;
}

// ALÍNEA D)

void listaC(ct *tab, int n){
    for (int i = 0; i < n; ++i) {
        printf("Nome e numero: %s | %d \n", tab[i].nome, tab[i].num);
    }
}

// ALÍNEA E)

int mostraNum(pct tab, char *nome, int n){
    for (int i = 0; i < n; ++i) {
        if(strcmp(nome,tab[i].nome) == 0){
            printf("Numero: %d", tab[i].num);
        }
    }
    return 0;
}

// ALÍNEA F)

void atualizaNum(ct *tab, char *nome,int n){
    int num = 0;

    for (int i = 0; i < n; ++i) {
        if(strcmp(nome,tab[i].nome) == 0){
            printf("\nNumero novo: ");
            scanf("%d", &num);
            tab[i].num = num;
        }
    }
}

// ALÍNEA G)

pct eliminaC(pct tab, char *nome, int *n){
    pct p;
    ct aux;

    for (int i = 0; i < *n; ++i) {
        if(strcmp(nome,tab[i].nome) == 0){
            aux = tab[i];
            tab[i] = tab[*n-1];
            p = realloc(tab, sizeof(ct)*(*n-1));
            if(p != NULL){
                tab = p;
                (*n)--;
            }else{
                tab[i] = aux;
            }
        }
    }
    return tab;
}

// ALÍNEA H)

