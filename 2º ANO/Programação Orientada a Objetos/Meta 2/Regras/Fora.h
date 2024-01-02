#ifndef NEWWORKPOO_FORA_H
#define NEWWORKPOO_FORA_H

#include "../Regra.h"

class Fora : public Regra {
public:
    Fora(Sensor *sensor, float valor1, float valor2);
    ~Fora() override;
    Fora(const Fora &outro);

    Fora* clone() const override;

    bool check() override;
private:
    float valor1, valor2;
};


#endif //NEWWORKPOO_FORA_H
