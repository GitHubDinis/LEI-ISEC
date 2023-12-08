#include "Pessoa.h"

// CONSTRUTOR

Pessoa::Pessoa(string nome, int bi, int nif) : nome(nome), bi(bi), nif(nif){
    cout << "Construtor de Pessoa" << endl;
}

// DESTRUTOR

Pessoa::~Pessoa() {
    cout << "Destrutor de Pessoa" << endl;
}

// FUNÇÕES MEMBRO (GETTERS)

string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getBI() const {
    return bi;
}

int Pessoa::getNIF() const {
    return nif;
}

// FUNÇÕES MEMBRO (SETTERS)

void Pessoa::setNome(string nome) {
    this->nome = nome;
}

void Pessoa::setBI(int bi) {
    this->bi = bi;
}

void Pessoa::setNIF(int nif) {
    this->nif = nif;
}

// FUNÇÕES MEMBRO

string Pessoa::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Nome: " << nome << ", " << "BI: " << bi << ", " << "NIF: " << nif << endl;
    return buffer0.str();
}











