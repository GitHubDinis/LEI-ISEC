#include "RegistoCivil.h"

RegistoCivil::RegistoCivil(const string &n): pais(n), total(0) {
    cout << "A construir Registo Civil " << pais << endl;
}
RegistoCivil::~RegistoCivil(){
    cout << "A destruir Registo Civil " << pais << endl;
}

string RegistoCivil::getAsString() const {
    ostringstream os;
    os << "Registo Civil " << pais << " com os " << total << " registos:\n";
    auto ptr = lista.begin();
    while (ptr < lista.end())
        if ((*ptr)->getBI() != 0)
            os << (*ptr)->getAsString();
    return os.str();
}

string RegistoCivil::getPais() const{
    return pais;
}

bool RegistoCivil::registaPessoa(Pessoa *pessoa) {
    if(pessoa == nullptr)
        return false;

    lista.push_back(pessoa);
    return true;
}

void RegistoCivil::obterPessoa(int bi) {
    auto ptr = lista.begin();
    while(ptr != lista.end()){
        if((*ptr)->getBI() == bi){
            (*ptr)->getAsString();
        } else{
            ptr++;
        }
    }
}







