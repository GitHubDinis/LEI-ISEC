#include "IgualA.h"

IgualA::IgualA(Sensor *sensor, float valor) : Regra(sensor, "iguala"), valor(valor) {
    cout << "Construtor de Regra IgualA!" << endl;
}

IgualA::~IgualA() {
    cout << "Destrutor de Regra IgualA!" << endl;
}

IgualA::IgualA(const IgualA &outro) : Regra(outro.sensor->clone(), outro.getNome()), valor(outro.valor) {

}

bool IgualA::check() {
    if(this->valor == this->sensor->medePropriedade()){
        return true;
    }

    return false;
}

IgualA *IgualA::clone() const {
    return new IgualA(*this);
}


