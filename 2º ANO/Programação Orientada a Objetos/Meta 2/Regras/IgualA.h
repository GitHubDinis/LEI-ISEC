#ifndef NEWWORKPOO_IGUALA_H
#define NEWWORKPOO_IGUALA_H

#include "../Regra.h"

class IgualA : public Regra {
public:
    IgualA(Sensor *sensor, float valor);
    ~IgualA() override;
    IgualA(const IgualA &outro);

    IgualA* clone() const override;

    bool check() override;
private:
    float valor;
};


#endif //NEWWORKPOO_IGUALA_H
