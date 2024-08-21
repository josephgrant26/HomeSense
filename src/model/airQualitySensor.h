#ifndef AIRQUALITYSENSOR_H
#define AIRQUALITYSENSOR_H

#include <string>
#include "sensor.h"
#include <unordered_map>
#include <vector>
#include <initializer_list>

using std::string;
using std::unordered_map;
using std::vector;

class AirQualitySensor: public Sensor{
private:

unordered_map<string, double> chemicalLevels;
const vector<string> setChemicals;

/*bool bO3, bNO2, bNO, bCO, bSO2, bH2S; 
double O3, NO2, NO, CO, SO2, H2S, dustLevel;
*/

public:

AirQualitySensor(const vector<string> &, string="new sensor");

void setSensor();

double getReading();

};

#endif
