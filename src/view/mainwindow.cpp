#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QWidget(parent), logo(new QLabel(this)), mainLayout(new QVBoxLayout(this)),
    sensors(new QVector<QPushButton*>), addSensorButton(new QPushButton(this)){


    connect(addSensorButton, &QPushButton::clicked, );

    QPixmap imgMap("C:/Users/josep/OneDrive/Documents/HomeSense/src/logo.png");
    logo->setPixmap(imgMap);
    addSensorButton->setText("Add Sensor");

    //test loader:

    sensorLoader();


    //main layout:
    mainLayout->addWidget(logo);
    mainLayout->addWidget(addSensorButton);
    displaySensors();


    //set main layout:

    this->setLayout(mainLayout);



}


void MainWindow::addSensors(string sensorName){

    QPushButton sensor;
    sensor.setText(QString::fromStdString(sensorName));

    sensors->push_back(&sensor);

    displaySensors();


}

void MainWindow::displaySensors(){

    for(QVector<QPushButton*>::iterator it = sensors->begin(); it != sensors->end(); ++it){

        mainLayout->addWidget(*it);

    }

}

void MainWindow::sensorLoader(){
    int i =0;
    for(i = 0; i<15; ++i){
        QPushButton* label = new QPushButton();
        label->setText(QString::number(i));
        sensors->push_back(label);
    }
}


