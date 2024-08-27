#include "motionSensor.h"

MotionSensor::MotionSensor(string name, double d): Sensor(name), radius(d), intruder(0), movement(false) {}

void MotionSensor::calibrate(double d){ radius=d; }

double MotionSensor::getCalibration() const { return radius; }

void MotionSensor::detectMovement(double d) {

    if(isOn()){
        movement = true;
        intruder = d;
    }

}

double MotionSensor::getReading() const {
    if(isMovementDetected())
        return intruder;

    return 0;
}

bool MotionSensor::isMovementDetected() const { return movement; }

void MotionSensor::reset() { movement = false; }
