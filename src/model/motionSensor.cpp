#include "motionSensor.h"

MotionSensor::MotionSensor(string name, double d): Sensor(name), radius(d), intruder(0), movement(false) {}

void MotionSensor::calibrate(double d){ radius=d; }

double MotionSensor::getCalibration() const { return radius; }

void MotionSensor::setValue(double d) {

    if(isOn()){
        movement = true;
        intruder = d;
    }

}

void MotionSensor::setMovement(){

    movement ? movement =false:movement = true;
}

double MotionSensor::getReading() const {
    if(isMovementDetected())
        return intruder;

    return 0;
}

bool MotionSensor::isMovementDetected() const { return movement; }

