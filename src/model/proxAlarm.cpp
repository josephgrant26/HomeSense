#include"proxAlarm.h"

ProxAlarm::ProxAlarm(double d, string name): MotionSensor(d,name), isAlarm(0) {}

void ProxAlarm::soundAlarm() { isAlarm=true; }

double ProxAlarm::getReading()
{return 0;}
