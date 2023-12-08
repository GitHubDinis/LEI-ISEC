#include <iostream>

#include "Ponto.h"
#include "Triangulo.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    // EXERCÍCIO 1
    // ALÍNEA A)
    Ponto a(1,2), b(3,4);

    cout << a.getAsString();
    cout << b.getAsString();

    // ALÍNEA B)
    a.distancia(b);

    // ALÍNEA C)
    const Ponto c(5,6);
    cout << c.getAsString();


    // ALÍNEA D)
    Ponto varios[3] = {Ponto(1,3), Ponto(2,4), Ponto(5,7)};
    cout << varios[0].getAsString();
    cout << varios[1].getAsString();
    cout << varios[2].getAsString();

    // ALÍNEA E)
    Ponto d;
    cout << d.getAsString();

    // EXERCÍCIO 2
    // ALÍNEA A)
    Triangulo t2("Professora", (1,2), (3,4), (5,6));
    Triangulo t1("Dinis", a, b, c);
    cout << t2.getAsString();
    cout << t1.getAsString();

    // ALÍNEA B)


    // ALÍNEA C)


    return 0;
}
