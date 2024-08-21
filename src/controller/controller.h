#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "src/view/view.h"
#include <vector>
#include <QVector>
#include <QPushButton>
#include <QObject>
//#include "src/model/sensor.h"
#include "src/model/proxAlarm.h"

using std::vector;

//class MainWindow;

class Controller: public QObject{

    Q_OBJECT

    MainWindow* home;
    SensorPanel* sensorPanel;
    vector<Sensor*>* sensors;
    View* view;

public:
    Controller(QObject* = nullptr);


    //window management:
    void InitHomeScreen();      //loads the home screen

    //vector and permanence
    QVector<QPushButton*> createQLabelVector();     //creates the QPushbutton to be displayed in home screen
    bool loadData(); //reads a JSON and loads the sensors to the vector
    bool saveData(); //reads a JSON or user inputs to add sensros to the array and the save file

public slots:

    //void handleClickedSensor();
    void openWindow(QWidget*);

};

#endif // CONTROLLER_H
