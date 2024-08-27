#ifndef AIRQUALITYSENSOR_H
#define AIRQUALITYSENSOR_H

#include <string>
#include "sensor.h"
#include <unordered_map>
#include <vector>
#include <tuple>


using std::string;
using std::unordered_map;
using std::vector;
using std::tuple;
using std::get;

class AirQualitySensor: public Sensor{
private:

    unordered_map<string, tuple<double,double>> chemicals;     //creates a umap of chemicals chemName: chemValue:chemMaxValue
                                                                // if chemValue > chemMaxValue turn on alarm
    bool isAlarm;

bool setLimits(const unordered_map<string, double>&);

public:

    AirQualitySensor(const unordered_map<string, tuple<double,double>>&, string="new sensor");

    void setSensor();
    void alarm();

    double getReading(string) const;
    unordered_map<string,double> getAllLimits() const;
    double getChemicalLimits(string) const;
    double getReading() const;  //returns overall status for all monitored chemicals: 0 = no issue
                                                                                //1 = one anomaly
                                                                                //2 = two or more anomalies
                                                                                //3 = error code

};

#endif
