#include"motionSensor.h"

class ProxAlarm: public MotionSensor{
private:

    bool isAlarm;

public:

ProxAlarm(double=0);

void soundAlarm();
void calibrate();

};