#ifndef NEWWORKPOO_REFRIGERADOR_H
#define NEWWORKPOO_REFRIGERADOR_H

#include "../Aparelho.h"

class Refrigerador : public Aparelho {
public:
    Refrigerador(vector<Propriedade*> propriedades);
    ~Refrigerador() override;
    Refrigerador(const Refrigerador &outro);

    void efeitoSeLigado() override;
    void efeitoAoDesligar() override;

    Refrigerador* clone() const override;
private:
    vector<Propriedade*> propriedades;
};


#endif //NEWWORKPOO_REFRIGERADOR_H
