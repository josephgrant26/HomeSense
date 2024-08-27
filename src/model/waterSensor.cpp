#include "waterSensor.h"

WaterSensor::WaterSensor(string name, double t): Sensor(name), leak(0), tollerance(t), isAlarm(0) {}

void WaterSensor::alarm() {
    if(leak>tollerance)
        isAlarm=true;
}

double WaterSensor::getReading() const { return leak; }

double WaterSensor::getTollerance() const{ return tollerance; }

void WaterSensor::setLeakTollerance(double t) {tollerance = t;}
