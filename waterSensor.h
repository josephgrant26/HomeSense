#include "sensor.h"

class WaterSensor: public Sensor{
private:
    double leak;
    bool isAlarm;

public:

    WaterSensor();

    void alarm();

    double getReading();

};