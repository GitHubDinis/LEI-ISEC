#include "Radiacao.h"

Radiacao::Radiacao(int valor) : Propriedade("radiacao", valor) {
    if(valor < 0){
        throw invalid_argument("Radiacao inferior a 0.");
    }
    cout << "Construtor de Radiacao!" << endl;
}
