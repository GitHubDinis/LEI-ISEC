#include "Temperatura.h"

Temperatura::Temperatura(float valor) : Propriedade("temperatura", valor){
    if(valor < -273){
        throw invalid_argument("Temperatura inferior a -273.");
    }
    cout << "Construtor de Temperatura!" << endl;
}
