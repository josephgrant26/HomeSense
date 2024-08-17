#include "newsensorwindow.h"

NewSensorWindow::NewSensorWindow(QWidget* parent): QWidget(parent), label(new QLabel(this)) {

    label->setText("addsensors");

}
