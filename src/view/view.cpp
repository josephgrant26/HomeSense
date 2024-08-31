#include "view.h"

View::View(MainWindow* h, AddSensor* a, SensorPanel* n, SensorGraphView* g, QWidget* parent): QWidget(parent), logo(new QLabel(this)),
    mainLayout(new QGridLayout(this)), home(h), addSensor(a), sensorPanel(n), sensorGraph(g),
    currentWidget(nullptr), homePage(new QPushButton("Main Page", this)){

    QPixmap imgMap(":images/images/logo.png");
    if(imgMap.isNull()) qDebug() << "Logo pathing wasn't correctly set. Current path is:" << QDir::currentPath();

    logo->setPixmap(imgMap.scaledToHeight(QApplication::primaryScreen()->size().height()*0.15, Qt::SmoothTransformation));
    homePage->setFixedSize(QApplication::primaryScreen()->size().width()*0.15,QApplication::primaryScreen()->size().height()*0.08);

    connect(homePage, &QPushButton::clicked, this, &View::goHome);

    mainLayout->addWidget(logo, 0,0, Qt::AlignCenter | Qt::AlignTop);
    mainLayout->addWidget(homePage, 0,1);
    setLayout(mainLayout);

}

void View::setCurrentWidget(QWidget* widget)
{
    if(currentWidget){
        currentWidget->hide();
        mainLayout->removeWidget(currentWidget);
    }

    mainLayout->addWidget(widget,2,0);
    currentWidget = widget;
    widget->show();

}

void View::setHome(const QVector<QPushButton*>& v){

    home->sensorLoader(v);
    home->displaySensors();
    setCurrentWidget(home);

}

QWidget* View::getCurrentWidget() const{
    return currentWidget;
}



