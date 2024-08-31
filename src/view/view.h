#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include <QScreen>
#include <QApplication>

#include "src/view/mainwindow.h"
#include "src/view/sensorpanel.h"
#include "src/view/addsensor.h"
#include "src/view/sensorgraphview.h"

class View: public QWidget
{
    Q_OBJECT
private:

    QLabel* logo;
    QGridLayout* mainLayout;
    MainWindow* home;
    AddSensor* addSensor;
    SensorPanel* sensorPanel;
    SensorGraphView* sensorGraph;
    QWidget* currentWidget;
    QPushButton* homePage;


public:

    View(MainWindow*, AddSensor*, SensorPanel*, SensorGraphView*, QWidget* =0);

    void setCurrentWidget(QWidget*);                //adds a widget to mainLayout
    void setHome(const QVector<QPushButton*>&);    //loads up the mainwindow including the saved sensors
    QWidget* getCurrentWidget() const;

signals:

    void goHome();

};

#endif // VIEW_H
