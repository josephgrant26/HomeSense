#ifndef NEWSENSORWINDOW_H
#define NEWSENSORWINDOW_H

#include <QWidget>
#include <QLabel>

class NewSensorWindow: public QWidget{
    Q_OBJECT

    QLabel* label;


public:
    NewSensorWindow(QWidget* =nullptr);
};

#endif // NEWSENSORWINDOW_H
