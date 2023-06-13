#include <stdio.h>
#include <string.h>

// EXERCICÍO 1

void rotacao(float *p1, float *p2, float *p3) {
    float t;

    t = *p3;
    *p3 = *p2;
    *p2 = *p1;
    *p1 = t;
}

// EXERCICÍO 4

void obtemInfo(int a[], int tam, int *np, int *ni, int *m, int *pos){
    *m = a[0];
    *np = 0;
    *ni = 0;

    for(int i = 0; i < tam; i++){
        if(a[i]%2 == 0){
            (*np)++;
        }else{
            (*ni)++;
        }
        if(a[i] > *m){
            *m = a[i];
            *pos = i;
        }
    }
}

// EXERCICÍO 3

void colocaZero(int a[], int tam){
    int soma = 0, media = 0;
    for(int i = 0; i < tam; i++){
        soma = soma + a[i];
    }

    media = soma / tam;

    for(int i = 0; i < tam; i++){
        if(a[i] < media)
            a[i] = 0;
    }

    for(int i = 0; i < tam; i++){
        printf("%d\t", a[i]);
    }
}

// EXERCICÍO 5

int comuns(int *tabA, int tamA, int *tabB, int tamB){
    int ncomuns = 0;

    for(int i = 0; i < tamA; i++){
        for(int j = 0; j < tamB; j++){
            if(tabA[i] == tabB[j])
                ncomuns++;
        }
    }
    printf("Comuns:%d\n", ncomuns);
}

// EXERCICÍO 7

void procuraDupla(int *tab, int tam, int *prim, int *seg){
    *prim = tab[0], *seg = 0;

    for(int i = 0; i < tam; i++){
        if(tab[i] < *seg){
            *seg = tab[i];
        }
    }
    for(int i = 0; i < tam; i++){
        if(tab[i] > *prim){
            *prim = tab[i];
        }
    }
    for(int i = 0; i < tam; i++){
        if(tab[i] < *prim && tab[i] > *seg){
            *seg = tab[i];
        }
    }
}

// EXERCICIO 14

void escreveMat(int nLin, int nCol, float a[][nCol]){
    int i, j;

    for(i=0; i<nLin; i++){
        for (j = 0; j < nCol; j++){
            printf("%4.1f\t",a[i][j]);
        }
        putchar('\n');
    }
}

// EXERCICÍO 18

void ex18(int nLin, int nCol, float a[][nCol], int *min, int *max){
    int  i, j;
    float media[6] = {0,0,0,0,0,0};
    float menor = a[0][0], maior = a[0][0];

    for(i = 0; i < nLin; i++){
        for(j = 0; j < nCol; j++){
            media[j] = media[j] + a[i][j];
        }
    }

    for(j = 0; j < nCol; j++){
        media[j] = media[j] / (float)nLin;
    }

    for (j = 0; j < nCol; j++){
        printf("%0.2f ", media[j]);
    }

    for(i = 0; i < nLin; i++){
        for(j = 0; j < nCol; j++){
            if(menor > media[j]){
                menor = media[j];
                *min = j;
            }
            if(maior < media[j]){
                maior = media[j];
                *max = j;
            }
        }
    }
}

// EXERCICÍO 20

void tradutor(char str[]){
    char *pt[] = {"Janeiro", "Fevereiro", "Marco", "Abril"};
    char *ing[] = {"January","February","March","April"};
    int i;

    for(i = 0; i < 4; i++){
        if(strcmp(str, pt[i]) == 0){
            printf("%s - %s\n", str, ing[i]);
            return;
        }
        printf("O mes %s e invalido!\n", str);
    }
}

// EXERCICÍO 22 (A)

void escreve_sin(char *sin[][2], int tot_lin){
    int i;

    for(i = 0; i < tot_lin; i++){
        printf("Palavra: %s , Sinonimo: %s", *sin[i], *(sin[i]+1));
        putchar('\n');
    }
}

// EXERCICÍO 22 (B)

char *pesquisa_sinonimo(char *sin[][2], int tot_lin, char *p){
    int i;

    for(i = 0; i < tot_lin; i++){
        if(strcmp(p, sin[i][0]) == 0){
            return sin[i][1];
        }
        if(strcmp(p, sin[i][1]) == 0){
            return sin[i][0];
        }
    }

    return NULL;
}

// MAIN

int main() {
    //float a = 1.0, b = 2.0, c = -3.5;

    int tab[8] = {-2,4,7,8,10,11,5,3};
    //int np, ni, m, pos;

    int tab1[8] = {1,2,3,4,5,6,7,8};
    int media;

    //int m, s;
    int tab2[8] = {4,-3,2,1,8,12,10,4};

    //rotacao(&a, &b, &c);
    //printf("A=%3.1f\tB=%3.1f\tC=%3.1f\n", a, b, c);

    //obtemInfo(tab, 8, &np, &ni, &m, &pos);
    //printf("Impares:%d\tPares:%d\n", ni, np);
    //printf("Maior:%d\tPos:%d\n", m, pos);

    //colocaZero(tab1, 8);

    //comuns(tab, 8, tab1, 8);

    //procuraDupla(tab2, 8, &m, &s);
    //printf("Maior:%d\t2Maior:%d", m, s);

    float m2[2][6] = {{1.0,1.6,4.2,1.4,0.5,-3.4},{2.5,8.1,0.9,-0.1,0.8,3.5}};
    int min2 = 0, max2 = 0;

    //escreveMat(2, 6, m2);

    //ex18(2,6,m2,&min2,&max2);
    //printf("Matriz m2: (%d, %d)\n", min2, max2);

    //char mes[100];
    //printf("Mes: ");
    //scanf("%s", mes);
    //tradutor(mes);

    char palavra[50], *p;
    char *s[5][2] = {{"estranho", "bizarro"},
                     {"desconfiar", "suspeitar"},
                     {"vermelho", "encarnado"},
                     {"duvidar", "desconfiar"},
                     {"carro", "automovel"}};

    escreve_sin(s, 5);		// alinea 22 A)

    printf("Palavra a pesquisar: ");
    scanf(" %s", palavra);
    p = pesquisa_sinonimo(s, 5, palavra); // alinea 22.2
    if(p == NULL)
        printf("A palavra %s nao tem sinonimo conhecido\n", palavra);
    else
        printf("A palavra %s e sinonimo de %s\n", p, palavra);


    return 0;
}
