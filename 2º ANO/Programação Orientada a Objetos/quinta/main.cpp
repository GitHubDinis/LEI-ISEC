#include <iostream>

#include "Pessoa.h"
#include "RegistoCivil.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    // EXERCÍCIO 6

    Pessoa p1("Dinis", 30799614, 2020130403);

    Pessoa p2("Professora", 123456789, 2134567891);

    //cout << p1.getAsString();

    //p1.setNome("Falconi");

    //cout << p1.getAsString();

    // EXERCÍCIO 7

    RegistoCivil r1("Portugal");

    cout << r1.getAsString();

    r1.adicionaPessoa(p1);
    r1.adicionaPessoa(p2);

    //cout << r1.obtemLista();

    return 0;
}
