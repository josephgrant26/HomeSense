#include "sensor.h"

Sensor::Sensor(string name): isInit(false), sensorName(name) {}

void Sensor::initialize() { isInit= true; }

string Sensor::getName(){ return sensorName; }
