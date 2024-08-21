#include "motionSensor.h"

MotionSensor::MotionSensor(double d, string name): Sensor(name), diameter(d) {}

void MotionSensor::calibrate(double d){ diameter=d; }
