#ifndef SENSOR_H
#define SENSOR_H

#include <string>

using std::string;

class Sensor{

private:

    bool isInit;
    string sensorName;

public:
    Sensor(string ="new sensor");
    virtual double getReading() const=0;
    void initialize(); //set init variable
    void off(); //turns off sensor
    bool isOn(); //tells us if the sensor is on or off
    string getName() const;

};

#endif
