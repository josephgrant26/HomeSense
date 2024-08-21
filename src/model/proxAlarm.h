#ifndef PROXALARM_H
#define PROXALARM_H
#include"motionSensor.h"

class ProxAlarm: public MotionSensor{
private:

    bool isAlarm;

public:

ProxAlarm(double=0, string="new sensor");

void soundAlarm();
//virtual void calibrate();
double getReading();

};

#endif
