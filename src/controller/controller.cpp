#include "controller.h"
Controller::Controller(QObject* parent): QObject(parent), home(new MainWindow()), sensorPanel(new SensorPanel()),
    sensors(new vector<Sensor*>), view(new View(home, sensorPanel)){

    connect(home, &MainWindow::openSensorPanel, this, [this] {openWindow(sensorPanel);});
    connect(sensorPanel, &SensorPanel::openHome, this, [this] {openWindow(home);});
    //temporary vec setter

    for(int i=0; i<10; ++i){
        ProxAlarm* alarm = new ProxAlarm(0,std::to_string(i));
        sensors->push_back(alarm);
    }
    InitHomeScreen();
    view->show();

}

void Controller::InitHomeScreen()
{

    view->SetHome(createQLabelVector());

}

QVector<QPushButton*> Controller::createQLabelVector(){

    QVector<QPushButton*> tmp;
    for(vector<Sensor*>::const_iterator it = sensors->cbegin(); it != sensors->cend(); ++it){
        QPushButton* btn = new QPushButton(QString::fromStdString((*it)->getName()));
        tmp.push_back(btn);
    }

    return tmp;
}

void Controller::openWindow(QWidget* w){ view->setCurrentWidget(w); }


