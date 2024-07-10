#include "motionSensor.h"

MotionSensor::MotionSensor(double d=0): diameter(d) {}

double MotionSensor::getReading(){ }

void MotionSensor::calibrate(double d){ diameter=d; }
