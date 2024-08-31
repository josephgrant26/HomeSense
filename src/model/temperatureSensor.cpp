#include "temperatureSensor.h"

TemperatureSensor::TemperatureSensor(string name, int temp): Sensor(name), currentTemp(temp) {}

double TemperatureSensor::getReading() const{

    return currentTemp;

}

void TemperatureSensor::setValue(double temp){
    currentTemp = temp;
}
