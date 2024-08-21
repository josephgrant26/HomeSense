#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "temperatureSensor.h"
class AirConditioner: public TemperatureSensor{
private:
    bool isCooling, isHeating;

public:

AirConditioner(string="new sensor");

double getReading();
void cool();
void heat();

};

#endif
