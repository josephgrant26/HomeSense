#include "view.h"

View::View(MainWindow* h, AddSensor* a, SensorPanel* n, QWidget* parent): QWidget(parent), logo(new QLabel(this)), mainLayout(new QGridLayout(this)), home(h)
    , addSensor(a), sensorPanel(n), currentWidget(nullptr), saveFile(new QPushButton( "Set Save Path", this)){

    QPixmap imgMap("../../images/logo.png");
    if(imgMap.isNull()) qDebug() << "Logo pathing wasn't correctly set. Current path is:" << QDir::currentPath();

    logo->setPixmap(imgMap);

    connect(saveFile, &QPushButton::clicked, this, &View::newSavePath);


    mainLayout->addWidget(logo, 0,0);
    mainLayout->addWidget(saveFile, 0, 3);
    setLayout(mainLayout);

    windowSize();

}
void View::windowSize(){

    QScreen *screen = QGuiApplication::primaryScreen();
    auto width = static_cast<int>(screen->geometry().width())*0.4;
    auto height = static_cast<int>(screen->geometry().height())*0.4;
    auto x = (screen->geometry().width() - 2*width)/2;
    auto y = (screen->geometry().height() - 1.5*height)/2;
    move(x,y);
    resize(762, 432);

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

void View::setHome(const QVector<QPushButton*>& v){

    home->sensorLoader(v);
    home->displaySensors();
    setCurrentWidget(home);

}



