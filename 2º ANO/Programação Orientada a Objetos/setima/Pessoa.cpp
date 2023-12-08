#include "Pessoa.h"

Pessoa::Pessoa(string nome, int bi, int nif) : nome(nome), bi(bi), nif(nif) {
    cout << "Contrutor de Pessoa!" << endl;
}

Pessoa::Pessoa() {
    cout << "Construtor de Pessoa!" << endl;
}

string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getBI() const {
    return bi;
}

int Pessoa::getNIF() const {
    return nif;
}

void Pessoa::setNome(string nome) {
    this->nome = nome;
}

string Pessoa::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Nome: " << nome << ", BI: " << bi << ", NIF: " << nif << endl;
    return buffer0.str();
}