#include "waterSensor.h"

WaterSensor::WaterSensor(string name, double t): Sensor(name), leak(0), tollerance(t), isAlarm(0) {}

void WaterSensor::toggleAlarm() {
    if(leak>tollerance)
        isAlarm=true;
    else
        isAlarm = false;
}

double WaterSensor::getReading() const { return leak; }

double WaterSensor::getTollerance() const{ return tollerance; }

void WaterSensor::setLeakTollerance(double t) { tollerance = t; }

void WaterSensor::setValue(double v){ leak=v; }
