#include "sensor.h"
class MotionSensor: public Sensor{
private:
    double diameter;

public:

    MotionSensor(double=0, string="new sensor");

    virtual void calibrate(double);
    
};
