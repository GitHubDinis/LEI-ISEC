#include <stdio.h>
#include "ponto.h"
#include "retangulo.h"
#include "outros.h"

// GUIÃO 2 (EXERCICÍO 3)

int main(){
    ret2D tab[10];
    int total = 0;

    addR(tab, &total);

    addR(tab, &total);

    //listaTodos(tab, total);

    //listaQuadrados(tab, total);

    //eliminaPequeno(tab, &total);

    //listaTodos(tab, total);

    eliminaInferior(tab, &total, 5);

    listaTodos(tab, total);
}

// GUIÃO 2 (EXERCICÍO 2)

/*int main(){
    ret2D r1 = {{4,2}, 12, 8}, r2;
    ponto2D p1 = {1,3};

    printR(r1);

    initR(&r2);

    printR(r2);

    areaR(r1);

    verificaR(r1, p1);

    deslocaR(r1, 10,10);

    return 0;
}*/

// GUIÃO 2 (EXERCÍCIO 1)

/*
int main(int argc, char** argv) {

    ponto2D p1 = {1,3}, p2, p3 = {4,5};

    initPonto(&p2);

    printPonto(p1);

    printPonto(p2);

    movePonto(&p1, 3, -2);
    printPonto(p1);

    verificaPonto(&p1, &p2, &p3);

    return 0;
}*/
