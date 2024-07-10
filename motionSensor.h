#include "sensor.h"
class MotionSensor: public Sensor{
private:
    double diameter;

public:

    MotionSensor(double=0);

    void calibrate(double);
    double getReading();
};