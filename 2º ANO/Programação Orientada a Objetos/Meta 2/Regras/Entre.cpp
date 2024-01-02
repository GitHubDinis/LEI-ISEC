#include "Entre.h"

Entre::Entre(Sensor *sensor, float valor1, float valor2) : Regra(sensor, "entre"), valor1(valor1), valor2(valor2) {
    cout << "Construtor de Regra Entre!" << endl;
}

Entre::~Entre() {
    cout << "Destrutor de Regra Entre!" << endl;
}

Entre::Entre(const Entre &outro) : Regra(outro.sensor->clone(), outro.getNome()), valor1(outro.valor1), valor2(outro.valor2) {

}

bool Entre::check() {
    if (this->valor1 < sensor->medePropriedade() || this->valor2 > sensor->medePropriedade()) {
        return true;
    }

    return false;
}

Entre *Entre::clone() const {
    return new Entre(*this);
}
