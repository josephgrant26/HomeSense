#include"proxAlarm.h"

ProxAlarm::ProxAlarm(string name, double d): MotionSensor(name,d), isAlarm(0) {}

void ProxAlarm::soundAlarm() {

    if(isMovementDetected()){
        isAlarm=true;
        reset();
    }
}




