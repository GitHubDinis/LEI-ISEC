#ifndef NEWWORKPOO_REGRA_H
#define NEWWORKPOO_REGRA_H

#include "Sensor.h"

#include <iostream>

using namespace std;

class Regra {
public:
    Regra(Sensor *sensor, string nome);
    virtual ~Regra();
    Regra(const Regra &outro);

    virtual Regra* clone() const = 0;

    int getID() const;
    string getNome() const;

    string getNomeSensor() const;
    string getIDSensor() const;

    virtual bool check() = 0;
private:
    int ID;
    string nome;
    char letra;
protected:
    Sensor *sensor;
};


#endif //NEWWORKPOO_REGRA_H
