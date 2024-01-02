#include "Refrigerador.h"

static int contaIt = 0;

Refrigerador::Refrigerador(vector<Propriedade*> propriedades) : Aparelho(propriedades, "refrigerador", 'r'), propriedades(propriedades) {
    cout << "Construtor de Aparelho Refrigerador!" << endl;
}

Refrigerador::~Refrigerador() {
    cout << "Destrutor de Aparelho Refrigerador!" << endl;
}

Refrigerador::Refrigerador(const Refrigerador &outro) : Aparelho(outro.propriedades, outro.getTipoOuComando(), outro.getLetra()), propriedades(outro.propriedades) {

}

void Refrigerador::efeitoSeLigado() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if(contaIt >= 3){
            if(contaIt % 3 == 0){
                if((*it)->getNome() == "temperatura"){
                    (*it)->setValor((*it)->getValor() - 1);
                    if((*it)->getValor() < -273){
                        (*it)->setValor(-273);
                    }
                }
            }
        } else if(contaIt == 1){
            if((*it)->getNome() == "som"){
                (*it)->setValor((*it)->getValor() + 20);
            }
        }
        it++;
    }
    contaIt++;
}

void Refrigerador::efeitoAoDesligar() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if((*it)->getNome() == "som"){
            (*it)->setValor((*it)->getValor() - 20);
            if((*it)->getValor() < 0){
                (*it)->setValor(0);
            }
            contaIt = 1;
        }
        it++;
    }
}

Refrigerador *Refrigerador::clone() const {
    return new Refrigerador(*this);
}
