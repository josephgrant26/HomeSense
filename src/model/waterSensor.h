#ifndef WATERSENSOR_H
#define WATERSENSOR_H
#include "sensor.h"

class WaterSensor: public Sensor{
private:
    double leak;    // in mL
    double tollerance;  //in mL
    bool isAlarm;

public:

    WaterSensor(string="new sensor", double =0);

    void alarm();
    double getReading() const;
    double getTollerance() const;
    void setLeakTollerance(double t);



};

#endif
