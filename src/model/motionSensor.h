#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H


#include "sensor.h"
class MotionSensor: public Sensor{
private:
    double radius;
    double intruder;
    bool movement;

public:

    MotionSensor(string="new sensor", double=0);

    void calibrate(double);     //sets range of action
    double getCalibration() const;  //returns range of action
    void detectMovement(double);  //turns movement to true if it detects movement and sets intruder location (distance in a straight line from sensor)
    bool isMovementDetected() const; //returns the movement value
    void reset();   //resets movement to false for future readings

    double getReading() const;  //shows last detected movement position (straight line from sensor)

    
};

#endif
