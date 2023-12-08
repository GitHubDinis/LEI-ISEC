#include <iostream>

#include "Prego.h"
#include "Aviso.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Prego p1(1, 2);
    cout << p1.getAsString();

    Aviso a1("Dinis em perigo!", p1);
    cout << a1.getAsString();

    Aviso a2("Professora marca falta!", p1);
    cout << a2.getAsString();

    p1.mudaDeSitio(5,5);
    cout << p1.getAsString();

    cout << a1.getAsString();

    return 0;
}
