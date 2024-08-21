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

AirQualitySensor::AirQualitySensor(const vector<string>& chemicals, string name): Sensor(name), setChemicals(chemicals) {

    //init umap:
    for(vector<string>::const_iterator it = setChemicals.cbegin(); it != setChemicals.cend(); ++it ){
        chemicalLevels.insert({*it, 0});
    }

}

double AirQualitySensor::getReading() {}

void AirQualitySensor::setSensor() {}
