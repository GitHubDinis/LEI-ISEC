#include <stdlib.h>
#include <stdio.h>

#include "pessoa.h"

int atribuiCod(){
    static int cod = 1;
    return cod++;
}

// ALÍNEA B)

pno adiciona(pno p){
    pno novo, aux;

    novo = malloc(sizeof(novo));
    if(novo == NULL) return p;
    printf("Dados: ");
    scanf("%s %d %f %f", novo->nome, &novo->id, &novo->peso, &novo->altura);
    novo->prox = NULL;

    /*while(p != NULL){
        if(novo->id == p->id){
            printf("Precisa de novo ID: ");
            scanf("%d", &novo->id);
        }
        p = p->prox;
    }*/

    if(p == NULL){
        p = novo;
    }else{
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return p;
}

// ALÍNEA C)

void listarTudo(pno p){
    while(p != NULL){
        printf("Nome: %s | ID: %d | Peso: %f | Altura: %f \n", p->nome, p->id, p->peso, p->altura);
        p = p->prox;
    }
}

// ALÍNEA D)

void atualizaPeso(pno p, int id, float novoPeso){
    while (p != NULL){
        if(p->id == id){
            p->peso = novoPeso;
            break;
        }
        p = p->prox;
    }
}

// ALÍNEA E)

pno elimina(pno p, int id){
    pno aux, anterior;
    aux = p; // aponta para o inicio
    anterior = NULL;

    while(aux != NULL && aux->id != id){  // procurar
        anterior = aux;
        aux = aux->prox;
    }

    if(aux == NULL) return p; // nao existe

    if(anterior == NULL){
        p = aux->prox;   // elimina o primeiro, p passa para o 2º elemento
    }else{
        anterior->prox = aux->prox; //  caso geral
    }

    free(aux); // libertar
    return p;
}