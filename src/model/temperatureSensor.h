#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H
#include "sensor.h"

class TemperatureSensor: public Sensor{
private:

    int currentTemp;

public:

TemperatureSensor(string="new sensor", int =0);


double getReading() const;
void setCurrentTemperature(int);

};

#endif
