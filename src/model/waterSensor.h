#ifndef WATERSENSOR_H
#define WATERSENSOR_H
#include "sensor.h"

class WaterSensor: public Sensor{
private:
    double leak;
    bool isAlarm;

public:

    WaterSensor(string="new sensor");

    void alarm();

    double getReading();

};

#endif
