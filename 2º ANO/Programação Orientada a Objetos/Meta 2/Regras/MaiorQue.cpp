#include "MaiorQue.h"

MaiorQue::MaiorQue(Sensor *sensor, float valor) : Regra(sensor, "maiorque"), valor(valor) {
    cout << "Construtor de Regra MaiorQue!" << endl;
}

MaiorQue::~MaiorQue()  {
    cout << "Destrutor de Regra MaiorQue!" << endl;
}

MaiorQue::MaiorQue(const MaiorQue &outro) : Regra(outro.sensor->clone(), outro.getNome()), valor(outro.valor) {

}

bool MaiorQue::check() {
    if(sensor->medePropriedade() > this->valor){
        return true;
    }

    return false;
}

MaiorQue *MaiorQue::clone() const {
    return new MaiorQue(*this);
}
