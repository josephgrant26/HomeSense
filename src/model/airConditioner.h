#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "temperatureSensor.h"
class AirConditioner: public TemperatureSensor{
private:
    bool isCooling, isHeating;
    double targetTemp;

public:

    AirConditioner(string="new sensor", int=0);

    void cool();    //starts cooling sequence
    void heat();    //starst heating sequence
    bool cooling(); //tells if aircon is cooling
    void setTargetTemp(double); //determines if the air conditioner should be heating or cooling
    double getTargetTemp()const;

};

#endif
