#ifndef NEWWORKPOO_SENSOR_H
#define NEWWORKPOO_SENSOR_H

#include <vector>

#include "Componente.h"
#include "Propriedade.h"

class Sensor : public Componente {
public:
    Sensor(Propriedade *propriedadeMedida);
    ~Sensor() override;
    Sensor(const Sensor &outro);

    float medePropriedade() const;

    virtual Sensor* clone() const;

    string getAsString() const override;
private:
    Propriedade *propriedadeMedida;
};


#endif //NEWWORKPOO_SENSOR_H
