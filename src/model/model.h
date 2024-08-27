#ifndef MODEL_H
#define MODEL_H

#include "./src/model/waterSensor.h"
#include "./src/model/airConditioner.h"
#include "./src/model/airQualitySensor.h"
#include "./src/model/motionSensor.h"
#include "./src/model/sensor.h"
#include "./src/model/temperatureSensor.h"
#include "./src/model/proxAlarm.h"

#include <QObject>


class model: public QObject{

    Q_OBJECT

public:
    model();
};

#endif // MODEL_H
