#include "sensor.h"
class AirQualitySensor: public Sensor{
private:
bool bO3, bNO2, bNO, bCO, bSO2, bH2S; 
double O3, NO2, NO, CO, SO2, H2S, dustLevel;
public:

AirQualitySensor(bool=0, bool=0, bool=0, bool=0, bool=0, bool=0, double=0, double=0, double=0, double=0, double=0, double=0, double=0);

void setSensor();

double getReading();

};