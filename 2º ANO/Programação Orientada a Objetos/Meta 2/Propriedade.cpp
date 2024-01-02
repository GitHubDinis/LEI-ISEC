#include "Propriedade.h"

Propriedade::Propriedade(string nome, float valor) : nome(nome), valor(valor) {
    cout << "Construtor de Propriedade!" << endl;
}

Propriedade::~Propriedade() {
    cout << "Destrutor de Propriedade!" << endl;
}

string Propriedade::getNome() const {
    return this->nome;
}

float Propriedade::getValor() const {
    return this->valor;
}

void Propriedade::setValor(float novoValor) {
    this->valor = novoValor;
}

string Propriedade::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Nome: " << this->nome << ", Valor Atual: " << this->valor;
    return buffer0.str();
}
