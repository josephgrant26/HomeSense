#include"proxAlarm.h"

ProxAlarm::ProxAlarm(double d=0): MotionSensor(d), isAlarm(0) {}

void ProxAlarm::soundAlarm() { isAlarm=true; }