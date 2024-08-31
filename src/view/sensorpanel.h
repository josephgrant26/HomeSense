#ifndef SENSORPANEL_H
#define SENSORPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>

class SensorPanel: public QWidget{
    Q_OBJECT

    //QLabel* label;
    QPushButton* loadFile;
    QPushButton* addSensor;
    QGridLayout* mainLayout;

public:
    SensorPanel(QWidget* =nullptr);


signals:

    void appendFile();
    void newSensor();
};

#endif // SENSORPANEL_H
