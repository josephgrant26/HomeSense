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
    virtual ~Sensor()= default;
    virtual double getReading() const=0;
    virtual void setValue(double) =0;
    void initialize(); //set init variable
    void off(); //turns off sensor
    bool isOn(); //shows if sesnor is on or off
    string getName() const; //returns sensor name


};

#endif
