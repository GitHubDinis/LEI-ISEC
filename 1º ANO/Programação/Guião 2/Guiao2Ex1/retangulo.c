#include <stdio.h>
#include "retangulo.h"

// alinea b)

void printR(ret2D r1){
    printf("Canto Inferior Esquerdo: x->%d, y->%d \n", r1.cie.x, r1.cie.y);
    printf("Canto Superior Esquerdo: x->%d, y->%d \n", r1.cie.x, r1.cie.y + r1.alt);
    printf("Canto Inferior Direito: x->%d, y->%d \n", r1.cie.x + r1.larg, r1.cie.y);
    printf("Canto Superior Direito: x->%d, y->%d \n", r1.cie.x + r1.larg, r1.cie.y + r1.alt);
}

// alinea c)

void initR(ret2D* p){
    printf("Canto Inferior Esquerdo: ");
    scanf("%d", &p->cie.x);
    scanf("%d", &p->cie.y);
    printf("Largura do Retangulo: ");
    scanf("%d", &p->larg);
    printf("Altura do Retangulo: ");
    scanf("%d", &p->alt);
}

// alinea d)

int areaR(ret2D r1){
    return r1.alt * r1.larg;
}

// alinea e)

int verificaR(ret2D r1, ponto2D p){
    if(p.x < r1.cie.x + r1.larg && p.x > r1.cie.x && p.y < r1.cie.y + r1.alt && p.y > r1.cie.y){
        return 1;
    }else{
        return 0;
    }
}

// alinea f)

void deslocaR(ret2D r1, int dx, int dy){
    r1.cie.x += dx;
    r1.cie.y += dy;
}
