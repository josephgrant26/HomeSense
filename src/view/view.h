#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
//#include "src/controller/controller.h"
#include "src/view/mainwindow.h"
#include "src/view/sensorpanel.h"

class View: public QWidget
{
    Q_OBJECT
private:

    QLabel* logo;
    QGridLayout* mainLayout;
    MainWindow* home;
    SensorPanel* sensorPanel;
    QWidget* currentWidget;


public:

    View(MainWindow*, SensorPanel*, QWidget* =0);

    void setCurrentWidget(QWidget*);
    void SetHome(const QVector<QPushButton*>&);    //loads up the mainwindow including the saved sensors

};

#endif // VIEW_H
