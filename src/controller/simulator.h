#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QMap>

#include "src/model/model.h"
#include "src/model/sensorgraph.h"
#include "src/view/sensorgraphview.h"


class Simulator: public QObject
{
    Q_OBJECT
private:

    Sensor* sensor;
    SensorGraph* sensorGraph;
    SensorGraphView *graphView;
    QTimer* timer;
    QElapsedTimer* elapsed;

public:
    Simulator(Sensor* , SensorGraph*, SensorGraphView*);
    string getCurrentSensor() const;
    void resetLabels() const;

public slots:
    void generateValues();


};

#endif // SIMULATOR_H
