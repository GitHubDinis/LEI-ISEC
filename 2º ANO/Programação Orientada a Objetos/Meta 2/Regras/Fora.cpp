//
// Created by Utilizador on 26/12/2023.
//

#include "Fora.h"

Fora::Fora(Sensor *sensor, float valor1, float valor2) : Regra(sensor, "fora"), valor1(valor1), valor2(valor2) {
    cout << "Construtor de Regra Fora!" << endl;
}

Fora::~Fora() {
    cout << "Desstrutor de Regra Fora!" << endl;
}

Fora::Fora(const Fora &outro) : Regra(outro.sensor->clone(), outro.getNome()), valor1(outro.valor1), valor2(outro.valor2) {

}

bool Fora::check() {
    if(this->valor1 > sensor->medePropriedade() || this->valor2 < sensor->medePropriedade()){
        return true;
    }

    return false;
}

Fora *Fora::clone() const {
    return new Fora(*this);
}
