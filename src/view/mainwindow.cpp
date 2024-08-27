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

void MainWindow::displaySensors(){
    int i = 1;
    for(QVector<QPushButton*>::iterator it = sensors->begin(); it != sensors->end(); ++it){

        mainLayout->addWidget(*it, i, 0);
        ++i;

    }

}

void MainWindow::sensorLoader(const QVector<QPushButton*>& v){
    clearPage();
    qDebug() << v;
    if(!sensors->isEmpty()){ sensors->clear(); qDebug() << sensors->empty();}
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



