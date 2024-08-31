#include "airConditioner.h"

AirConditioner::AirConditioner(string name, int temp): TemperatureSensor(name, 0), isCooling(false), isHeating(false),
    targetTemp(temp){}

void AirConditioner::cool() {
    if(isOn()){
        if(isHeating) isHeating = false;

        isCooling=true;
    }

}

void AirConditioner::heat() {
    if(isOn()){
        if(isCooling) isCooling = false;

        isHeating=true;
    }
}

bool AirConditioner::cooling(){
    return isCooling;
}

void AirConditioner::setTargetTemp(double t){
    targetTemp = t;
}

double AirConditioner::getTargetTemp() const{
    return targetTemp;
}
