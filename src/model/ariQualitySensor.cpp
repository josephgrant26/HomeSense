#include"airQualitySensor.h"
#include <QDebug>

AirQualitySensor::AirQualitySensor(const unordered_map<string, tuple<double,double>>& chem, string name): Sensor(name),
    chemicals(chem), isAlarm(false) {}

double AirQualitySensor::getReading() const{
    int cont = 0;

    for(auto it = chemicals.cbegin(); it != chemicals.cend(); ++it){

        if(get<0>(it->second) > get<1>(it->second)){
            cont ++;
        }
    }

    if(cont == 0) return 0;     //monitored chemicals are all below threshold
    if (cont == 1) return 1;    //one chemical is above threshold
    return 2;                   //there is more than one chemical above threshold
}

double AirQualitySensor::getReading(string chemical) const{

    for(auto it = chemicals.cbegin(); it != chemicals.cend(); ++it){
        if(it->first==chemical){
            qDebug() << "chemval: " << get<0>(it->second) << "lim: " << get<1>(it->second);
            qDebug("");
            return get<0>(it->second);

        }
    }

    return 0;
}

unordered_map<string, double> AirQualitySensor::getAllLimits() const{

    unordered_map<string, double> tmp;
    for(auto it = chemicals.cbegin(); it != chemicals.cend(); ++it){
        tmp.insert({it->first, get<1>(it->second)});
    }

    return tmp;

}

double AirQualitySensor::getChemicalLimits(string chemical) const{

    for(auto it = chemicals.cbegin(); it != chemicals.cend(); ++it){
        if(it->first == chemical){
            return get<1>(it->second);
        }
    }

    return 0;
}

void AirQualitySensor::toggleAlarm() {
    if(isAlarm)
        isAlarm=false;
    else
        isAlarm=true;
}

void AirQualitySensor::setValue(string c, double v) {
    for(auto it = chemicals.begin(); it != chemicals.end(); ++it){
        if(it->first==c){
            get<0>(it->second) = v;

        }
    }
}

void AirQualitySensor::setValue(double d){
    for(auto it = chemicals.begin(); it!= chemicals.end(); ++it){
        get<0>((it)->second) = d;
    }
}
