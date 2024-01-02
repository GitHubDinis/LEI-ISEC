#include "MenorQue.h"

MenorQue::MenorQue(Sensor *sensor, float valor) : Regra(sensor, "menorque"), valor(valor) {
    cout << "Construtor de Regra MenorQue!" << endl;
}

MenorQue::~MenorQue() {
    cout << "Destrutor de Regra MenorQue!" << endl;
}

MenorQue::MenorQue(const MenorQue &outro) : Regra(outro.sensor->clone(), outro.getNome()), valor(outro.valor) {

}

bool MenorQue::check() {
    if(sensor->medePropriedade() < this->valor){
        return true;
    }

    return false;
}

MenorQue *MenorQue::clone() const {
    return new MenorQue(*this);
}
