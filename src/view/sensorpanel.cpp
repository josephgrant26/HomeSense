#include "sensorpanel.h"

SensorPanel::SensorPanel(QWidget* parent): QWidget(parent), loadFile(new QPushButton("load files", this)), addSensor(new QPushButton("add single sensor", this)),
    back(new QPushButton("backHome", this)), mainLayout(new QGridLayout(this)) {


    connect(back, &QPushButton::clicked, this, &SensorPanel::openHome);
    connect(loadFile, &QPushButton::clicked, this, &SensorPanel::appendFile);
    connect(addSensor, &QPushButton::clicked, this, &SensorPanel::newSensor);

    mainLayout->addWidget(back, 0,0);
    mainLayout->addWidget(addSensor, 2, 1);
    mainLayout->addWidget(loadFile, 1, 1);


    setLayout(mainLayout);
}
