#include <iostream>

#include "Habitacao.h"
#include "Componente.h"
#include "Processador.h"
#include "Propriedades/Fumo.h"

#include "Simulador.h"

using namespace std;

/*int main() {
    cout << "Hello, World!" << endl;

    Habitacao h1(3, 3);
    h1.adicionaZona(2, 2);
    h1.adicionaZona(1, 1);
    h1.adicionaZona(1, 2);

    cout << h1.getAsString();

    h1.removeZona(2);

    cout << h1.getAsString();
    cout << "\n\n";

    cout << "ZONA 1: " << h1.listaPropriedades(1) << "\n\n";
    cout << "ZONA 3: " << h1.listaPropriedades(3) << "\n\n";

    h1.modificaValorPropriedade(1, "temperatura", 50);

    cout << "ZONA 1 (ALTERADA):" << h1.listaPropriedades(1) << "\n\n";
    cout << "ZONA 3 (ALTERADA): " << h1.listaPropriedades(3) << "\n\n";

    Propriedade *p1 = new Fumo(40);
    cout << "PROPRIEDADE: " << p1->getAsString();

    p1->setValor(56);

    cout << p1->getAsString();

    return 0;
}*/

int main(){

    Simulador s1;

    s1.iniciaInterface();

    return 0;
}