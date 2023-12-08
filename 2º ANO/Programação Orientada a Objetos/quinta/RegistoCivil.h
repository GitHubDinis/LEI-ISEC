#ifndef QUINTA_REGISTOCIVIL_H
#define QUINTA_REGISTOCIVIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Pessoa.h"

using namespace std;

class RegistoCivil {
    const static int max = 20;
    Pessoa *conjunto[max];
    string pais;
public:
    RegistoCivil(string pais);
    ~RegistoCivil();

    bool adicionaPessoa(Pessoa &p);
    bool apagaPessoa(int BI);
    bool adicionaPesssoaFicheiro();

    void obtemNome(int BI);
    string obtemLista();
    void alteraNome(int BI, string nome);
    void obtemNumeroPessoas();

    string getPais() const;

    string getAsString() const;
};


#endif //QUINTA_REGISTOCIVIL_H
