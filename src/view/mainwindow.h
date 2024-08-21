#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <iostream>



using std::string;
using std::cout;



class MainWindow: public QWidget
{
    Q_OBJECT

private:

    QGridLayout* mainLayout;
    QVector<QPushButton*>* sensors;
    QPushButton* addSensorButton;




public:
    MainWindow(QWidget* = nullptr);

    void displaySensors(); //displays QVector on window

    void sensorLoader(const QVector<QPushButton*>&); //loads sensors from controller to QVector

signals:

    void openSensorPanel();



};

#endif // MAINWINDOW_H
