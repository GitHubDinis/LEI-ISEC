#include "Som.h"

Som::Som(int valor) : Propriedade("som", valor) {
    if(valor < 0){
        throw invalid_argument("Som inferior a 0.");
    }
    cout << "Construtor de Som!" << endl;
}
