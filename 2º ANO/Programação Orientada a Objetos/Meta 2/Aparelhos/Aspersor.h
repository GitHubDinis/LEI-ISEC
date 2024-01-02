#ifndef NEWWORKPOO_ASPERSOR_H
#define NEWWORKPOO_ASPERSOR_H

#include "../Aparelho.h"

class Aspersor : public Aparelho {
public:
    Aspersor(vector<Propriedade*> propriedades);
    ~Aspersor() override;
    Aspersor(const Aspersor &outro);

    void efeitoSeLigado() override;
    void efeitoAoDesligar() override;

    Aspersor* clone() const override;
private:
    vector<Propriedade*> propriedades;
};


#endif //NEWWORKPOO_ASPERSOR_H
