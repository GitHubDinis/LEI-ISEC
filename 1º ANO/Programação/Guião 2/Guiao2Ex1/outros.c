#include "outros.h"

// alínea b)

int addR(struct retangulo a[], int *p){
    if(*p == 10){
        printf("Tabela esta completa!");
    }else{
        initR(&a[*p]);
        ++(*p);
    }
}

// alínea c)

void listaTodos(struct retangulo a[], int tam){
    for(int i = 0; i < tam; i++){
        printf("Retangulo %d:\n", i);
        printR(a[i]);
    }
}

// alínea d)

void listaQuadrados(struct retangulo a[], int tam){
    for(int i = 0; i < tam; i++){
        if(a[i].larg == a[i].alt){
            printf("Quadrado %d: \n", i);
            printR(a[i]);
        }
    }
}

// alínea e)

int eliminaPequeno(struct retangulo a[], int *p){
    int area[*p];
    int menorArea = 0;

    // colocar em apenas um ciclo

    for(int i = 0; i < *p; i++){
        area[i] = areaR(a[i]);
        menorArea = area[0];
        if (area[i] < menorArea){
            menorArea = area[i];
        }
    }
    for (int i = 0; i < *p; i++){
        printf("Area: %d %d", area[i], menorArea);
        if(area[i] == menorArea){
            printf("Retangulo eliminado: %d\n", i);
            a[i] = a[*p - 1];
            --(*p);
            return 1;
        }
    }
}

// alinea f)

int eliminaInferior(struct retangulo a[], int *p, int lim){
    /* Solução do professor
    int le, esc = 0;
    for(le = 0; le < *tot; le++){
        if(areaR(a[le]) >= lim){
            a[esc++] = a[le];
        }
     }
     *tot = esc;
    */
    for(int i = 0; i < *p; i++){
        if(areaR(a[i]) < lim){
            printf("Retangulo eliminado: %d\n", i);
            a[i] = a[*p - 1];
            i--;
            --(*p);
        }
    }
}

// alinea g)

/*
void ordenaRet(struct retangulo a[], int tam){
    int dist[tam];
    for(int i = 0; i < tam; i++){
        dist[i] =
    }
}*/
