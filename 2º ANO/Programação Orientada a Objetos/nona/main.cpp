#include <iostream>

#include "Imobiliaria.h"
#include "Apartamento.h"
#include "Loja.h"
#include "RegistoPredial.h"

using namespace std;

// EXERCÍCIO 1 (FICHA 8)

int main() {
    cout << "Hello, World!" << endl;

    Imobiliaria imo1("Remax");
    Imobiliaria imo2("Era");

    RegistoPredial dono;

    dono.acrescenta(new Apartamento(100, 5, 2)); // T2
    dono.acrescenta(new Loja(50));
    dono.acrescenta(new Apartamento(80, 5, 1));

    cout << imo1.getAsString() << imo2.getAsString();

    imo1.acrescenta(dono.pesquisa("apartamento1"));
    imo1.acrescenta(dono.pesquisa("loja2"));
    imo2.acrescenta(dono.pesquisa("apartamento1"));
    imo1.acrescenta(dono.pesquisa("apartamento3"));

    cout << imo1.getAsString() << imo2.getAsString();
    cout << imo1.listaPorAndar(5);

    imo2.removePorCodigo("apartamento1");
    cout << "Depois de Remover: " << imo2.getAsString();

    cout << "FIM" << endl;

    cout << *dono.pesquisa("apartamento3");
    cout << *dono.pesquisa("loja2");

    return 0;
}
