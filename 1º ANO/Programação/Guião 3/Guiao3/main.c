#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"

#define N 4

// GUIÃO 3
// EXERCICÍO 1 (ACABAR E FAZER 2)

int main() {
    // ALÍNEA A)
    pno lista = NULL;
    int i;

    for(i = 0; i < 3; i++){
        lista = adiciona(lista);
    }
    listarTudo(lista);

    atualizaPeso(lista, 70, 2);

    lista = elimina(lista, 3);

    printf("Lista apos eliminar: \n");

    listarTudo(lista);

    return 0;
}

/*typedef struct concorrente no, *pno;

struct concorrente{
    char nome[200];		*//* nome do concorrente *//*
    int id;				*//* n.� de aluno: identificador �nico *//*
    float analise;		*//* n�vel de �lcool no sangue *//*
    pno prox;
};


// Funcao para criar a estrutura dinamica com base na informacao do ficheiro de texto
void cria_listas(pno tab[], char *n1)
{
    FILE *f;
    pno novo;
    int i, x, y;

    f = fopen(n1, "r");
    if(f==NULL)
    {
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
    while(fscanf(f, " %d %d", &x, &y) == 2)
    {
        for(i=0; i<y; i++)
        {
            novo = malloc(sizeof(no));
            if(novo == NULL)
            {
                printf("Erro na alocacao de memoria\n");
                fclose(f);
                return;
            }
            fscanf(f, " %d %f %[^\n]", &novo->id, &novo->analise, novo->nome);
            novo->prox = tab[x];
            tab[x] = novo;
        }
    }
    fclose(f);
}

void mostraListas(pno t[]) {
    pno aux;
    for (int i = 0; i < N; i++) {
        aux = t[i];
        while(aux != NULL){
            printf("%s\t%d\t%.2f\n", aux->nome, aux->id, aux->analise);
            aux = aux->prox;
        }
        printf("\n");
    }
}

int getProvas(pno t[], int id){
    pno aux;
    static int corridas;

    for(int i = 0; i < N; i++){
        aux = t[i];
        while (aux != NULL){
            if(id == aux->id){
                corridas++;
            }
            aux = aux->prox;
        }
    }

    return corridas;
}

pno cria_insere(pno t[], char s[], int id){
    pno novo;



    return *t;
}

pno criaNovaLista(pno t[]) {
    pno lista = NULL, aux = t[0];

    while (aux != NULL) {
        if (getProvas(&aux, aux->id) == N) {
            lista = cria_insere(lista, aux->nome, aux->id);
        }
        aux = aux->prox;
    }
    return lista;
}

void elimina(pno t[], int x){
    pno aux = *t;

    while(aux != NULL){

        aux = aux->prox;
    }
}*/

/*int main()
{
    // Declaracao do array de ponteiros
    pno tab[N] = {NULL};
    pno lista = NULL;
    int x;

    // Criar ED
    cria_listas(tab, "dados_11.txt");

    // Continuar a partir daqui ...
    mostraListas(tab);  // A)

    x = getProvas(tab, 315);
    printf("%d", x);

    lista = criaNovaLista(tab); // B

    //elimina(tab, 315);

    return 0;
}*/



