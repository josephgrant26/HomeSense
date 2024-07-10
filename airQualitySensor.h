#include "sensor.h"
class AirQualitySensor: public Sensor{
private:

double O3, NO2, NO, CO, SO2, H2S, dustLevel;
public:

AirQualitySensor(double=0, double=0, double=0, double=0, double=0);

void setSensor();
};