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

    void loadChart(QChart*, QVector<QString>);
    void unloadChart();
    vector<tuple<string,double>> newValues();
    QString getChartTitle() const;

public slots:

    void buttonLabel();
    void setLabel(QString);

signals:

    void turnedOn();
    void turnedOff();
    void changedValues();
    void removedSensor();

};

#endif // SENSORGRAPHVIEW_H
