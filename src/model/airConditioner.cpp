#include "airConditioner.h"

AirConditioner::AirConditioner(string name, int temp): TemperatureSensor(name, temp), isCooling(false), isHeating(false) {}

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
