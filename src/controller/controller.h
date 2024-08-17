#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "src/view/mainwindow.h"
#include <vector>
#include <QObject>
#include "src/view/newsensorwindow.h"
//#include "sensor.h"

using std::vector;

class controller: public QObject{

    Q_OBJECT

    MainWindow* mainWindow;
    NewSensorWindow* newSensors;
    //vector<Sensor*> sensors;

public:
    controller(MainWindow*, QObject* = nullptr);


    //window management:
    void openNewSensorWindow();
    void closeNewSensorWindow();
    void openSensorWindow();
    void closeSensorWindow();

    //vector and permanence
    bool loadData(); //reads a JSON and loads the sensors to the vector
    bool saveData(); //reads a JSON or user inputs to add sensros to the array and the save file

public slots:

    void handleClickedSensor();

};

#endif // CONTROLLER_H
