#include "Aparelho.h"

Aparelho::Aparelho(vector<Propriedade*> propriedades, string nome, char letra) : Componente(letra, "aparelho", nome), propriedades(propriedades), nome(nome), letra(letra){
    ligado = false;
    cout << "Contrutor de Aparelho" << endl;
}

Aparelho::~Aparelho() {
    cout << "Destrutor de Aparelho" << endl;
}

Aparelho::Aparelho(const Aparelho &outro) : Componente(outro), nome(outro.nome), ligado(outro.ligado), letra(outro.letra) {
    for (const auto &propriedade : outro.propriedades) {
        Propriedade *copiaPropriedade = new Propriedade(*propriedade);
        propriedades.push_back(copiaPropriedade);
    }
}

void Aparelho::setLigado(bool novoLigado) {
    this->ligado = novoLigado;
}

bool Aparelho::getLigado() const {
    return this->ligado;
}

string Aparelho::getAsString() const {
    ostringstream buffer0;
    string soma = this->getLetra() + to_string(this->getIDnum());
    buffer0 << "Tipo: " << soma << ", Nome: " << this->nome << ", Valor: " << endl;
    return buffer0.str();
}

string Aparelho::getComandoReconhecido(int pos) const {
    return comandos.at(pos);
}
