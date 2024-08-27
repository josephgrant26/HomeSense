#ifndef PROXALARM_H
#define PROXALARM_H
#include"motionSensor.h"

class ProxAlarm: public MotionSensor{
private:

    bool isAlarm;

public:

ProxAlarm( string="new sensor", double=0);

void soundAlarm();  //sets isAlarm to true




};

#endif
