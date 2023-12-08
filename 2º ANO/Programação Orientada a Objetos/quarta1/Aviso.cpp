#include "Aviso.h"

// CONSTRUTOR

Aviso::Aviso(string texto, Prego &p) : texto(texto){
    this->p = &p;
    cout << "Contrutor de Aviso: " << texto << endl;
}

// DESTRUTOR

Aviso::~Aviso() {
    cout << "Destrutor de Aviso: " << texto << endl;
}

string Aviso::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Prego:" << p->getAsString() << "Texto: " << texto << endl;
    return buffer0.str();
}



