#include "airConditioner.h"

AirConditioner::AirConditioner(): TemperatureSensor(), isCooling(false), isHeating(false) {}

double AirConditioner::getReading() {}

void AirConditioner::cool() { isCooling=true; }

void AirConditioner::heat() { isHeating=true; }