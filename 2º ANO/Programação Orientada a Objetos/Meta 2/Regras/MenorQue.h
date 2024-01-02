#ifndef NEWWORKPOO_MENORQUE_H
#define NEWWORKPOO_MENORQUE_H

#include "../Regra.h"

class MenorQue : public Regra {
public:
    MenorQue(Sensor *sensor, float valor);
    ~MenorQue() override;
    MenorQue(const MenorQue &outro);

    MenorQue* clone() const override;

    bool check() override;
private:
    float valor;
};


#endif //NEWWORKPOO_MENORQUE_H
