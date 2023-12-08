#ifndef SETIMA_REGISTOCIVIL_H
#define SETIMA_REGISTOCIVIL_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Pessoa.h"

using namespace std;

class RegistoCivil {
public:
    RegistoCivil(const string &n);
    ~RegistoCivil();
    bool registaPessoa(Pessoa *pessoa);
    string getAsString()const;
    string getPais() const;
    void obterPessoa(int bi);
private:
    vector<Pessoa*>lista;
    string pais;
    int total;
};


#endif //SETIMA_REGISTOCIVIL_H
