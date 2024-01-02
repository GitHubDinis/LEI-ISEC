#ifndef NEWWORKPOO_MAIORQUE_H
#define NEWWORKPOO_MAIORQUE_H

#include "../Regra.h"

class MaiorQue : public Regra {
public:
    MaiorQue(Sensor *sensor, float valor);
    ~MaiorQue() override;
    MaiorQue(const MaiorQue &outro);

    MaiorQue* clone() const override;

    bool check() override;
private:
    float valor;
};


#endif //NEWWORKPOO_MAIORQUE_H
