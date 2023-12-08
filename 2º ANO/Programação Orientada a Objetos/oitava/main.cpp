#include <iostream>

#include "Ponto.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    // ALÍNEA A)
    Ponto *a = new Ponto(1, 2);
    Ponto *b = new Ponto(3, 4);

    // ALÍNEA B)
    int numero = 3;
    //Ponto *arrayUni = new Ponto[numero]; // Precisa do construtor por omissão
    Ponto **arrayUni = new Ponto*[numero]; // Um * para Ponteiros dentro do array e outro * para dimensão

    arrayUni[0] = new Ponto(1, 2);
    arrayUni[1] = new Ponto(5, 6);
    arrayUni[2] = new Ponto(1, 2);

    // ALÍNEA C)
    int linhas = 2, colunas = 3;
    Ponto ***arrayBi = new Ponto **[linhas]; // Um * para Ponteiros dentro do array e outro * para cada dimensão

    for (int i = 0; i < linhas; i++) {
        arrayBi[i] = new Ponto * [colunas];
    }
    arrayBi[1][1] = new Ponto(1, 2);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arrayBi[i][j] = nullptr;
        }
    }

    // APAGAR
    delete a;
    delete b;
    for (int i = 0; i < numero; i++) {
        delete arrayUni[i];
    }
    delete[] arrayUni;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            delete arrayBi[i][j];
        }
    }
    delete[] arrayBi;

    return 0;
}
