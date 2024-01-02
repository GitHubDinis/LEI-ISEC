#include "Fumo.h"

Fumo::Fumo(int valor) : Propriedade("fumo", valor) {
    if(valor < 0 || valor > 100){
        throw invalid_argument("Fumo inferior a 0 ou superior a 100.");
    }
    cout << "Construtor de Fumo!" << endl;
}

Fumo::~Fumo() {
    cout << "Destrutor de Fumo!" << endl;
}
