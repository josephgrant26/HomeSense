#include "sensorgraph.h"

SensorGraph::SensorGraph(QString n, const QVector<QString>& names, double axisMin, double axisMax): series(new QVector<QLineSeries*>), axisX(new QValueAxis(this)), axisY(new QValueAxis(this)) {

    setTitle(n);

    axisY->setRange(axisMin,axisMax);
    axisX->setRange(0, 500);

    addAxis(axisX, Qt::AlignBottom);
    addAxis(axisY, Qt::AlignLeft);

    for(auto it = names.cbegin(); it != names.cend(); ++it){
        QLineSeries* s = new QLineSeries();
        s->setName(*it);
        series->push_back(s);
    }

    for(auto it = series->cbegin(); it != series->cend(); ++it){
        addSeries((*it));
        (*it)->attachAxis(axisX);
        (*it)->attachAxis(axisY);
    }



}

void SensorGraph::updateSeries(string n, double x, double y){

    for(auto it = series->cbegin(); it != series->cend(); ++it){
        if(QString::fromStdString(n) == (*it)->name())
            (*it)->append(x,y);
    }
    update();
}

void SensorGraph::clearGraph(){
    for(auto it = series->begin(); it != series->end(); ++it){
        (*it)->clear();

    }
}

double SensorGraph::getCurrrentValue(QString seriesName) const{
    for(auto it = series->cbegin(); it != series->cend(); ++it){
        if((*it)->name() == seriesName){
            return (*it)->points().last().y();
        }
    }
    return 0;
}



