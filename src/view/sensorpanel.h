#ifndef SENSORPANEL_H
#define SENSORPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SensorPanel: public QWidget{
    Q_OBJECT

    QLabel* label;
    QPushButton* back;

public:
    SensorPanel(QWidget* =nullptr);

signals:
    void openHome();
};

#endif // SENSORPANEL_H
