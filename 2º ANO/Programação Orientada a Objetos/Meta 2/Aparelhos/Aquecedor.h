#ifndef NEWWORKPOO_AQUECEDOR_H
#define NEWWORKPOO_AQUECEDOR_H

#include "../Aparelho.h"

class Aquecedor : public Aparelho {
public:
    Aquecedor(vector<Propriedade*> propriedades);
    ~Aquecedor() override;
    Aquecedor(const Aquecedor &outro);

    void efeitoSeLigado() override;
    void efeitoAoDesligar() override;

    Aquecedor* clone() const override;
private:
    vector<Propriedade*> propriedades;
};


#endif //NEWWORKPOO_AQUECEDOR_H
