#include "Luz.h"

Luz::Luz(int valor) : Propriedade("luz", valor){
    if(valor < 0){
        throw invalid_argument("Luz inferior a 0.");
    }
    cout << "Construtor de Luz!" << endl;
}
