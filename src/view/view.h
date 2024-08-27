#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include <QScreen>

#include "src/view/mainwindow.h"
#include "src/view/sensorpanel.h"
#include "src/view/addsensor.h"

class View: public QWidget
{
    Q_OBJECT
private:

    QLabel* logo;
    QGridLayout* mainLayout;
    MainWindow* home;
    AddSensor* addSensor;
    SensorPanel* sensorPanel;
    QWidget* currentWidget;
    QPushButton* saveFile;
    void windowSize();


public:

    View(MainWindow*, AddSensor*, SensorPanel*, QWidget* =0);

    void setCurrentWidget(QWidget*);
    void setHome(const QVector<QPushButton*>&);    //loads up the mainwindow including the saved sensors

signals:
    void newSavePath();

};

#endif // VIEW_H
