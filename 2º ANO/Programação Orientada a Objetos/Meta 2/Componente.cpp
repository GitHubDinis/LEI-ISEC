#include "Componente.h"

static int id = 1;

Componente::Componente(char letra, string nome, string tipoOuComando) : letra(letra), nome(nome), tipoOuComando(tipoOuComando) {
    ostringstream os;
    this->ID = id;
    os << letra << id++ << nome;
    tipo = os.str();
    cout << "Construtor de Componente!" << endl;
}

Componente::~Componente() {
    cout << "Destrutor de Componente!" << endl;
}

string Componente::getTipo() const {
    return this->tipo;
}

int Componente::getIDnum() const {
    return this->ID;
}

char Componente::getLetra() const {
    return this->letra;
}

string Componente::getTipoOuComando() const {
    return this->tipoOuComando;
}

void Componente::setComando(string novoComando) {
    this->tipoOuComando =  novoComando;
}
