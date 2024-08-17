#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QVector>
#include <QPushButton>
#include <iostream>
//#include "src/controller/controller.h"


using std::string;
using std::cout;



class MainWindow: public QWidget
{
    Q_OBJECT

private:

    QLabel *logo;
    QVBoxLayout* mainLayout;
    QVector<QPushButton*>* sensors;
    QPushButton* addSensorButton;



public:
    MainWindow(QWidget* = nullptr);

    void addSensors(string sensorName);

    void displaySensors();

    void sensorLoader();

signals:

    void createdArray();



};

#endif // MAINWINDOW_H
