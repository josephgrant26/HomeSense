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
    virtual double getReading()=0;
    void initialize(); //set init variable
    string getName();

};

#endif
