#include "sensorpanel.h"

SensorPanel::SensorPanel(QWidget* parent): QWidget(parent), label(new QLabel(this)), back(new QPushButton("backHome", this)) {

    label->setText("addsensors");
    connect(back, &QPushButton::clicked, this, &SensorPanel::openHome);

}
