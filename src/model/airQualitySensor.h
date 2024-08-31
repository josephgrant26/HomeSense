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

    unordered_map<string, tuple<double,double>> chemicals;     //chemical name: <chemical value,chemical limit>
    bool isAlarm;


public:

    AirQualitySensor(const unordered_map<string, tuple<double,double>>&, string="new sensor");

    void toggleAlarm();

    double getReading(string) const;
    unordered_map<string,double> getAllLimits() const;      //returns chemichal names : chemical limit
    double getChemicalLimits(string) const;                 //returns specific limit of "chemical name"
    double getReading() const;  //returns overall status for all monitored chemicals: 0 = no issue
        //1 = one anomaly
        //2 = two or more anomalies
        //3 = error code


    virtual void setValue(string, double);
    virtual void setValue(double);                                  //sets the value to all chemicals



};

#endif
