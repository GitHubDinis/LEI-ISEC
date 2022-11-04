#include <iostream>
#include "ponto.h"

// AULA 8
// EXERCICÍO 1 (Ficha 3)

using namespace std;

int main() {

    ponto p1(1,2);

    cout << "X: " << p1.getX() << endl;
    cout << "Y: " << p1.getY() << endl;
    cout << endl;

    ponto p2(3,4);

    cout << "X: " << p2.getX() << endl;
    cout << "Y: " << p2.getY() << endl;
    cout << endl;

    cout << "Distancia: " << p1.distancia(p2) << endl;

    return 0;
}
