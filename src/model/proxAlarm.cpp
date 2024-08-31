#include"proxAlarm.h"

ProxAlarm::ProxAlarm(string name, double d): MotionSensor(name,d), isAlarm(0) {}

void ProxAlarm::toggleAlarm() {

    if(isMovementDetected()){
        if(!isAlarm)
            isAlarm=true;
    }
    if(isAlarm)
        isAlarm=false;
}




