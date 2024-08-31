#include "sensorpanel.h"

SensorPanel::SensorPanel(QWidget* parent): QWidget(parent), loadFile(new QPushButton("load files", this)),
    addSensor(new QPushButton("add single sensor", this)), mainLayout(new QGridLayout(this)) {


    connect(loadFile, &QPushButton::clicked, this, &SensorPanel::appendFile);
    connect(addSensor, &QPushButton::clicked, this, &SensorPanel::newSensor);


    mainLayout->addWidget(addSensor);
    mainLayout->addWidget(loadFile);


    setLayout(mainLayout);
}
