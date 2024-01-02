#ifndef NEWWORKPOO_ENTRE_H
#define NEWWORKPOO_ENTRE_H

#include "../Regra.h"

class Entre : public Regra {
public:
    Entre(Sensor *sensor, float valor1, float valor2);
    ~Entre() override;
    Entre(const Entre &outro);

    Entre* clone() const override;

    bool check() override;
private:
    float valor1, valor2;
};


#endif //NEWWORKPOO_ENTRE_H
