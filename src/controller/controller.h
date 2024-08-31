#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "src/view/view.h"
#include "src/model/model.h"
#include "src/model/sensorgraph.h"
#include "simulator.h"

#include <QVector>
#include <QPushButton>
#include <QObject>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QScreen>
#include <QJsonArray>
#include <QStandardPaths>


using std::vector;

//class MainWindow;

class Controller: public QObject{

    Q_OBJECT

    MainWindow* home;
    SensorPanel* sensorPanel;
    AddSensor* addSensor;
    SensorGraphView* graphView;
    SensorGraph* sensorGraph;
    Simulator* simulator;
    vector<Sensor*>* sensors;
    QString savePath;
    View* view;

    QJsonDocument saveDataDoc();
    Sensor* getSensor(QString);

public:
    Controller(QObject* = nullptr);


    //window management:
    void createView();
    void InitHomeScreen();      //loads the home screen

    //vector and permanence
    QVector<QPushButton*> createQLabelVector();     //creates the QPushbutton to be displayed in home screen
    QVector<tuple<QLineEdit*, QDoubleSpinBox*>> createAQMVec(); //creates the AQMVector to be displayed in addSensor screen

    bool newSensor();                               //creates a single new sensor and writes it in savePath
    bool initData();
    bool loadData(QJsonDocument); //reads a JSON and loads the sensors to the vector
    bool saveData() const; //reads a JSON or user inputs to add sensors to the array and the save file
    bool addData(QJsonDocument); //receives a new JSON document, updates saveData file and sensors vector
    QString getStandardSaveLocation() const;
    bool removeSensor(QString);


public slots:

    //void handleClickedSensor();
    void openWindow(QWidget*);
    QString fileDialog();
    QJsonDocument fileToDoc(QString);
    void displayValueDesc();    //shows correct QLabel text for addSensor view
    bool createNewSensor();     //creates new sensor, displays it in Home and saved it so savePath file
    void openSensorGraph(QString);
    void openSimluator(QString);
    void closeSimulator();
    void updateData();


signals:
    void newData();
    void refreshGraphs();

};

#endif // CONTROLLER_H
