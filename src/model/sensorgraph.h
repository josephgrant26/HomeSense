#ifndef SENSORGRAPH_H
#define SENSORGRAPH_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

#include  "src/model/model.h"

class SensorGraph: public QChart
{
    Q_OBJECT
private:

    QVector<QLineSeries*>* series;
    QValueAxis* axisX;
    QValueAxis* axisY;

public:
    SensorGraph(QString, const QVector<QString>&, double=0, double=100);
    void updateSeries(string, double, double);
    void clearGraph();
    double getCurrrentValue(QString) const;

};

#endif // SENSORGRAPH_H
