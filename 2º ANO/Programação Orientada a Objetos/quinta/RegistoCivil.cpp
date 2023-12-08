//
// Created by Utilizador on 26/10/2023.
//

#include "RegistoCivil.h"

// CONSTRUTOR

RegistoCivil::RegistoCivil(string pais) : pais(pais) {
    for (int i = 0; i < max; i++) {
        conjunto[i] = nullptr;
    }
    cout << "Construtor de RegistoCivil" << endl;
}

// DESTRUTOR

RegistoCivil::~RegistoCivil() {
    cout << "Destrutor de RegistoCivil" << endl;
}

// FUNÇÕES MEMBRO (GETTERS)

string RegistoCivil::getPais() const {
    return pais;
}

// FUNÇÕES MEMBRO

bool RegistoCivil::adicionaPessoa(Pessoa &p) {
    for(int i = 0; i < max; i++){
        while(conjunto[i] != nullptr){
            if(conjunto[i]->getBI() == p.getBI()){
                cout << "Pessoa existente!" << endl;
                return false;
            }
        }
        if(conjunto[i] == nullptr) {
            conjunto[i] = &p;
            cout << "Pessoa adicionada!" << endl;
            return true;
        }
    }
    cout << "Numero maximo de pessoas!" << endl;
    return false;
}

bool RegistoCivil::apagaPessoa(int BI) {
    for (int i = 0; i < max; i++) {
        while (conjunto[i] != nullptr){
            if(conjunto[i]->getBI() == BI){

                cout << "Pessoa apagada!" << endl;
                return true;
            }
        }
    }
    cout << "Pessoa inexistente!" << endl;
    return false;
}

bool RegistoCivil::adicionaPesssoaFicheiro() {
    ifstream file("file.txt");
    if(file){
        string line;
        int index = 0;
        while(getline(file, line)){
            istringstream is(line);
            string nome;
            int BI, NIF;
            if(is >> nome && is >> BI && is >> NIF) {
                if(index < max){
                    Pessoa novaPessoa(nome, BI, NIF);
                    conjunto[index++] = &novaPessoa;
                }
            }
        }
    }
    return false;
}

string RegistoCivil::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Pais: " << pais << endl;
    return buffer0.str();
}

void RegistoCivil::obtemNome(int BI) {
    for (int i = 0; i < max; i++) {
        if(conjunto[i]->getBI() == BI){
            cout << "Nome: " << conjunto[i]->getNome() << endl;
        }
    }
}

string RegistoCivil::obtemLista() {
    ostringstream buffer0;
    for (int i = 0; i < max; ++i) {
        while (conjunto[i] != nullptr) {
            buffer0 << conjunto[i]->getNome() << endl;
        }
    }
    return buffer0.str();
}

void RegistoCivil::alteraNome(int BI, string nome) {
    for (int i = 0; i < max; ++i) {
        while(conjunto[i] != nullptr){
            if(conjunto[i]->getBI() == BI){
                conjunto[i]->setNome(nome);
            }
        }
    }
}

void RegistoCivil::obtemNumeroPessoas() {
    static int count = 0;
    for (int i = 0; i < max; i++) {
        while(conjunto[i] != nullptr){
            count++;
        }
    }
    cout << "Numero de pessoas: " << count << endl;
}
