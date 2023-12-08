//
// Created by Utilizador on 30/11/2023.
//

#include "Apartamento.h"

Apartamento::Apartamento(int area, int andar, int n_assoal) : Imovel(10.0 * area, area, andar, "Apartamento") {
    this->n_assoal = n_assoal;
}

Apartamento::~Apartamento() {
    cout << "A destruir apartamento" << endl;
}

int Apartamento::getNAssoal() const {
    return this->n_assoal;
}

string Apartamento::getAsString() const {
    ostringstream os;
    os << "N. Assoalhadas: " << this->n_assoal << ", " << Imovel::getAsString();
    return os.str();
}
