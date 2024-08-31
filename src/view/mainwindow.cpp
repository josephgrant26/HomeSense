#include "mainwindow.h"
#include "QDir"

MainWindow::MainWindow(QWidget* parent): QWidget(parent), mainLayout(new QGridLayout(this)),
    sensors(new QVector<QPushButton*>), addSensorButton(new QPushButton( "Add Sensors" ,this)){

    connect(addSensorButton, &QPushButton::clicked, this, &MainWindow::openSensorPanel);

    //main layout:
    mainLayout->addWidget(addSensorButton, 0, 0);


    //set main layout:
    this->setLayout(mainLayout);


}

MainWindow::~MainWindow(){
    if(sensors){
        for(auto it = sensors->begin(); it != sensors->end(); ++it){
            delete (*it);
        }
        delete sensors;
    }
}

void MainWindow::removeSensors(){

    for(auto it = sensors->begin(); it != sensors->end(); ++it){
        mainLayout->removeWidget((*it));
        delete (*it);
    }
    sensors->clear();
    mainLayout->update();

}

void MainWindow::displaySensors(){

    int i = 1;
    for(QVector<QPushButton*>::iterator it = sensors->begin(); it != sensors->end(); ++it){

        mainLayout->addWidget(*it, i, 0);
        QPushButton* button = *it;
        connect(*it, &QPushButton::clicked, this, [this, button] {emit sensorClicked((button)->text());});
        ++i;

    }

}

void MainWindow::sensorLoader(const QVector<QPushButton*>& v){
    clearPage();
    if(!sensors->isEmpty()){ sensors->clear(); }
    for(QVector<QPushButton*>::ConstIterator it = v.cbegin(); it != v.cend(); ++it){
        sensors->push_back(*it);
    }
}

void MainWindow::clearPage(){

    for(QVector<QPushButton*>::iterator it = sensors->begin(); it != sensors->end(); ++it){

        mainLayout->removeWidget(*it);
        delete(*it);
    }
}



