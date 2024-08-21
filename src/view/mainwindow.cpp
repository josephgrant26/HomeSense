#include "mainwindow.h"
#include "QDir"

MainWindow::MainWindow(QWidget* parent): QWidget(parent), mainLayout(new QGridLayout(this)),
    sensors(new QVector<QPushButton*>), addSensorButton(new QPushButton(this)){
    addSensorButton->setText("Add Sensor");

    connect(addSensorButton, &QPushButton::clicked, this, &MainWindow::openSensorPanel);

    //main layout:
    mainLayout->addWidget(addSensorButton);


    //set main layout:
    this->setLayout(mainLayout);


}

void MainWindow::displaySensors(){

    for(QVector<QPushButton*>::iterator it = sensors->begin(); it != sensors->end(); ++it){

        mainLayout->addWidget(*it);

    }

}

void MainWindow::sensorLoader(const QVector<QPushButton*>& v){

    for(QVector<QPushButton*>::ConstIterator it = v.cbegin(); it != v.cend(); ++it){
        sensors->push_back(*it);
    }
}



