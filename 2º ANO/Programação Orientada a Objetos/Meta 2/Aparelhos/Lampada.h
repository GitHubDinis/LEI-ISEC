#ifndef NEWWORKPOO_LAMPADA_H
#define NEWWORKPOO_LAMPADA_H

#include "../Aparelho.h"

class Lampada : public Aparelho {
public:
    Lampada(vector<Propriedade*> propriedades);
    ~Lampada() override;
    Lampada(const Lampada &outro);

    void efeitoSeLigado() override;
    void efeitoAoDesligar() override;

    Lampada* clone() const override;
private:
    vector<Propriedade*> propriedades;
};


#endif //NEWWORKPOO_LAMPADA_H
