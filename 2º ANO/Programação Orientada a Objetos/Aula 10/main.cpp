#include <iostream>
#include "ponto.h"
#include "retangulo.h"

// AULA 10
// EXERCICÍO 4 (Ficha 3)

using namespace std;

int main() {

    ponto p1(1,2);
    cout << "p1: " << p1.getAsString() << "\n";

    retangulo a(p1, 5, 10);
    cout << "a: " << a.getAsString() << "\n";
    cout << "area: " << a.area() << "\n";

    retangulo r2(a);
    cout << "r2: " << r2.getAsString() << "\n";
    cout << "area: " << r2.area() << "\n";



    return 0;
}
