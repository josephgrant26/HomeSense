#include "controller.h"

controller::controller(MainWindow* window, QObject* parent): QObject(parent), mainWindow(window), newSensors(new NewSensorWindow()) {

    mainWindow->show();
}
