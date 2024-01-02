#include "Sensor.h"

Sensor::Sensor(Propriedade *propriedadeMedida) : Componente('s', "sensor", propriedadeMedida->getNome()), propriedadeMedida(propriedadeMedida) {
    cout << "Construtor de Sensor!" << endl;
}

Sensor::~Sensor() {
    cout << "Destrutor de Sensor!" << endl;
}

Sensor::Sensor(const Sensor &outro) : Componente(outro), propriedadeMedida(new Propriedade(*(outro.propriedadeMedida))) {

}

Sensor* Sensor::clone() const {
    return new Sensor(*this);
}

float Sensor::medePropriedade() const {
    return this->propriedadeMedida->getValor();
}

string Sensor::getAsString() const {
    ostringstream buffer0;
    string soma = this->getLetra() + to_string(this->getIDnum());
    buffer0 << "Tipo: " << soma << ", Nome: " << this->getTipoOuComando() << ", Valor: " << this->medePropriedade() << endl;
    return buffer0.str();
}
