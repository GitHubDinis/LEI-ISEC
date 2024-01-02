#include "Humidade.h"

Humidade::Humidade(int valor) : Propriedade("humidade", valor) {
    if(valor < 0 || valor > 100){
        throw invalid_argument("Humidade inferior a 0 ou superior a 100.");
    }
    cout << "Construtor de Humidade!" << endl;
}
