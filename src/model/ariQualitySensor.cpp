#include"airQualitySensor.h"
//bool bO3, bNO2, bNO, bCO, bSO2, bH2S;
/*AirQualitySensor::AirQualitySensor(bool o=0, bool n2=0, bool n=0, bool c=0, bool s=0, bool h=0, 
                                    double O=0, double N2=0, double N=0, double C=0, double S=0, double H=0, double d=0): Sensor(),
                                    bO3(o), bNO2(n2), bNO(n), bCO(c), bH2S(s) {

                                        if(d>3) dustLevel=0;
                                        else{ dustLevel=d;}

                                        if(bO3) O3=O;
                                        if(bNO2) NO2=N2;
                                        if(bNO) NO=N;
                                        if(bCO) CO=C;
                                        if(bH2S) H2S=H;
                                        if(bSO2) SO2=S;

                                    }

*/

AirQualitySensor::AirQualitySensor(const unordered_map<string, tuple<double,double>>& chem, string name): Sensor(name), chemicals(chem), isAlarm(false) {



}

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
        if(it->first==chemical)
            return get<0>(it->second);
    }

    return 0;
}

unordered_map<string, double> AirQualitySensor::getAllLimits() const{

    unordered_map<string, double> tmp;
    for(auto it = chemicals.cbegin(); it != chemicals.cend(); ++it){
        tmp.insert({it->first, get<0>(it->second)});
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

void AirQualitySensor::alarm() { isAlarm=true; }
