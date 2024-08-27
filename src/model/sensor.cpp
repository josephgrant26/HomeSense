#include "sensor.h"

Sensor::Sensor(string name): isInit(false), sensorName(name) {}

void Sensor::initialize() { isInit= true; }

string Sensor::getName() const{ return sensorName; }

void Sensor::off() { isInit = false; }

bool Sensor::isOn() { return isInit;}
