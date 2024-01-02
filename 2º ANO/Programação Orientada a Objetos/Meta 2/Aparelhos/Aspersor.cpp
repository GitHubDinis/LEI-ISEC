#include "Aspersor.h"

static int contaIt = 1;

Aspersor::Aspersor(vector<Propriedade*> propriedades) : Aparelho(propriedades, "aspersor", 's'), propriedades(propriedades) {
    cout << "Construtor de Aparelho Aspersor!" << endl;
}

Aspersor::~Aspersor() {
    cout << "Destrutor de Aparelho Aspersor!" << endl;
}

Aspersor::Aspersor(const Aspersor &outro) : Aparelho(outro.propriedades, outro.getTipoOuComando(), outro.getLetra()), propriedades(outro.propriedades) {

}

void Aspersor::efeitoAoDesligar() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if(contaIt == 6){
            if((*it)->getNome() == "ruido"){
                (*it)->setValor((*it)->getValor() - 100);
                if((*it)->getValor() < 0){
                    (*it)->setValor(0);
                }
                contaIt = 1;
            }
        }
        it++;
    }
    contaIt++;
}

void Aspersor::efeitoSeLigado() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if(contaIt == 1){
            if((*it)->getNome() == "humidade"){
                (*it)->setValor((*it)->getValor() + 50);
                if((*it)->getValor() > 75){
                    (*it)->setValor(75);
                }
            } else if((*it)->getNome() == "vibracao"){
                (*it)->setValor((*it)->getValor() + 100);
            }
        } else if(contaIt == 2){
            if((*it)->getNome() == "fumo"){
                (*it)->setValor(0);
            }
            contaIt = 1;
            return;
        }
        it++;
    }
    contaIt++;
}

Aspersor *Aspersor::clone() const {
    return new Aspersor(*this);
}
