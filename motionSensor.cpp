#include "motionSensor.h"

MotionSensor::MotionSensor(double d=0): Sensor(), diameter(d) {}

void MotionSensor::calibrate(double d){ diameter=d; }
