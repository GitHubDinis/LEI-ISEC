#include <stdio.h>
#include "ponto.h"

// alinea b)
void printPonto(ponto2D a){
    printf("Ponto: (%d,%d)\n", a.x, a.y);
}

// alinea c)
void initPonto(ponto2D* p){
    printf("Coordenada X: \n");
    scanf("%d", &p->x);

    printf("Coordenada Y: \n");
    scanf("%d", &p->y);
}

// alinea d)
void movePonto(ponto2D* p, int dx, int dy){
    p->x += dx;
    p->y += dy;
}

// alinea e)
int verificaPonto(ponto2D* p1, ponto2D* p2, ponto2D* p3){
    if(p1->x == p2->x || p1->x == p3->x){
       return 1;
    }else if(p1->y == p2->y || p1->y == p3->y){
        return 1;
    }else{
        return 0;
    }
    // FALTA DIAGONAL
}