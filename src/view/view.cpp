#include "view.h"

View::View(MainWindow* h, SensorPanel* n, QWidget* parent): QWidget(parent), logo(new QLabel(this)), mainLayout(new QGridLayout(this)), home(h)
    , sensorPanel(n), currentWidget(nullptr){

    QPixmap imgMap("../../images/logo.png");
    if(imgMap.isNull()) qDebug() << "Logo pathing wasn't correctly set. Current path is:" << QDir::currentPath();

    logo->setPixmap(imgMap);

    mainLayout->addWidget(logo, 0,0);
    setLayout(mainLayout);

}

void View::setCurrentWidget(QWidget* widget)
{
    if(currentWidget){
        currentWidget->hide();
        mainLayout->removeWidget(currentWidget);
    }

    mainLayout->addWidget(widget,1,0);
    currentWidget = widget;
    widget->show();

}

void View::SetHome(const QVector<QPushButton*>& v){

    home->sensorLoader(v);
    home->displaySensors();
    setCurrentWidget(home);

}
