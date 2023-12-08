#include <iostream>

#include "RegistoCivil.h"
#include "Pessoa.h"

// Registo Civil (Ficha 4) -> Aplicar no TP
// Usar vectores na Meta 1

// FICHA 6 (EXERCÍCIO 1 E 2)

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    RegistoCivil r1("Portugal");
    cout << r1.getAsString();

    Pessoa p1("Dinis", 30799614, 2020130403);
    cout << p1.getAsString();

    r1.registaPessoa(&p1);
    cout << r1.getAsString();

    return 0;
}

