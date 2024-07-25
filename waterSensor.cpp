#include "waterSensor.h"

WaterSensor::WaterSensor(): Sensor(), leak(0), isAlarm(0) {}

void WaterSensor::alarm() { isAlarm=true; }

double WaterSensor::getReading() {}