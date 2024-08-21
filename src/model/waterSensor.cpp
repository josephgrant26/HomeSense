#include "waterSensor.h"

WaterSensor::WaterSensor(string name): Sensor(name), leak(0), isAlarm(0) {}

void WaterSensor::alarm() { isAlarm=true; }

double WaterSensor::getReading() {return 0;}
