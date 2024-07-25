#include "temperatureSensor.h"
class AirConditioner: public TemperatureSensor{
private:
    bool isCooling, isHeating;

public:

AirConditioner();

double getReading();
void cool();
void heat();

};