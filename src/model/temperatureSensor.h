#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H
#include "sensor.h"

class TemperatureSensor: public Sensor{
private:

    int temp;

public:

TemperatureSensor(string="new sensor");


};

#endif
