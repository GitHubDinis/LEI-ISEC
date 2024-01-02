#include "Regra.h"

static int id = 1;

Regra::Regra(Sensor *sensor, string nome) : sensor(sensor), nome(nome) {
    letra = 'r';
    ID = id++;
    cout << "Construtor de Regra!" << endl;
}

Regra::~Regra() {
    cout << "Destrutor de Regra!" << endl;
}

Regra::Regra(const Regra &outro) : ID(outro.ID), nome(outro.nome), letra(outro.letra), sensor(outro.sensor->clone()) {

}

int Regra::getID() const {
    return this->ID;
}

string Regra::getNome() const {
    return this->nome;
}

string Regra::getNomeSensor() const {
    return this->sensor->getTipoOuComando();
}

string Regra::getIDSensor() const {
    return this->sensor->getTipo();
}
