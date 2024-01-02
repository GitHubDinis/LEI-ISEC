#include "Vibracao.h"

Vibracao::Vibracao(int valor) : Propriedade("vibracao", valor) {
    if(valor < 0){
        throw invalid_argument("Vibracao inferior a 0.");
    }
    cout << "Construtor de Vibracao!" << endl;
}
