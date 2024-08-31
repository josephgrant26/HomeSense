#ifndef SENSORGRAPHVIEW_H
#define SENSORGRAPHVIEW_H

#include <QWidget>
#include <QChartView>
#include <QPushButton>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>

#include <tuple>

using std::tuple;
using std::vector;
using std::string;
using std::get;

class SensorGraphView: public QWidget{
    Q_OBJECT

private:
    QPushButton* removeSensor;
    QPushButton* toggleSensor;
    QPushButton* toggleValues;
    QGridLayout* mainLayout;

    QChartView* graphView;
    QChart* currentChart;

    QVector<tuple<QLabel*,QDoubleSpinBox*>>* values;
    QLabel* label;
    bool isGraph;


public:
    SensorGraphView();
    ~SensorGraphView();

    void loadChart(QChart*, QVector<QString>);      //puts graph in graph view
    void unloadChart();
    vector<tuple<string,double>> newValues();       //gets all modified values
    QString getChartTitle() const;
    void setLabel(QString);                         //labels the modifiable values


public slots:

    void buttonLabel();

signals:

    void turnedOn();
    void turnedOff();
    void changedValues();
    void removedSensor();

};

#endif // SENSORGRAPHVIEW_H
