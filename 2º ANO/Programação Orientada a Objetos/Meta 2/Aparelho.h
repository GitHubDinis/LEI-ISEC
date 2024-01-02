#ifndef NEWWORKPOO_APARELHO_H
#define NEWWORKPOO_APARELHO_H

#include <vector>

#include "Componente.h"
#include "Propriedade.h"

class Aparelho : public Componente {
public:
    Aparelho(vector<Propriedade*> propriedades, string nome, char letra);
    virtual ~Aparelho() override;
    Aparelho(const Aparelho &outro);

    void setLigado(bool novoLigado);
    bool getLigado() const;

    string getComandoReconhecido(int pos) const;

    virtual void efeitoSeLigado() = 0;
    virtual void efeitoAoDesligar() = 0;

    virtual Aparelho* clone() const = 0;

    string getAsString() const override;
private:
    string nome;
    bool ligado;
    char letra;
    vector<string> comandos = {"liga", "desliga"};
    vector<Propriedade*> propriedades;
};

#endif //NEWWORKPOO_APARELHO_H