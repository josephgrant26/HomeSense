#include "sensorgraphview.h"

SensorGraphView::SensorGraphView(): removeSensor(new QPushButton("Remove Sensor",this)), toggleSensor(new QPushButton("turn ON", this)),
    toggleValues(new QPushButton("set new values",this)), mainLayout(new QGridLayout(this)), graphView(new QChartView()),
    currentChart(nullptr), values(nullptr), label(new QLabel("Alarm is OFF", this)), isGraph(false){


    connect(toggleSensor, &QPushButton::clicked, this, &SensorGraphView::buttonLabel);
    connect(toggleValues, &QPushButton::clicked, this, &SensorGraphView::changedValues);
    connect(removeSensor, &QPushButton::clicked, this, &SensorGraphView::removedSensor);

    label->hide();
    mainLayout->addWidget(toggleSensor, 0,0);
    mainLayout->addWidget(graphView, 1,0);
    mainLayout->addWidget(removeSensor, 2,0);

}

void SensorGraphView::loadChart(QChart* c, QVector<QString> vals){

    graphView->setChart(c);
    values = new QVector<tuple<QLabel*,QDoubleSpinBox*>>;
    for(auto it = vals.cbegin(); it != vals.cend(); ++it){
        values->push_back(std::make_tuple(new QLabel((*it)),new QDoubleSpinBox));
    }
    int i =1;

    for(auto it = values->cbegin(); it != values->cend(); ++it){
        mainLayout->addWidget((get<0>(*it)),0,i);
        mainLayout->addWidget((get<1>(*it)),0,i+1);
        i = i+2;
    }
    mainLayout->addWidget(toggleValues, 0,i);
    if(!isGraph) delete currentChart;

    currentChart = c;
    isGraph = true;

}

void SensorGraphView::unloadChart(){

    if(isGraph){
        if(values){
            for(auto it = values->cbegin(); it != values->cend(); ++it){
                get<0>(*it)->hide();
                get<1>(*it)->hide();
            }
            delete values;
        }
        label->hide();
        QChart* tmp = new QChart();
        tmp->setTitle("empty");
        currentChart = tmp;
        graphView->setChart(currentChart);
        isGraph = false;
    }

}

vector<tuple<string, double> > SensorGraphView::newValues(){
    vector<tuple<string, double> > vec;
    for(auto it = values->cbegin(); it != values->cend(); ++it){
        vec.push_back(std::make_tuple(get<0>(*it)->text().toStdString(), get<1>(*it)->value()));
    }
    return vec;

}

QString SensorGraphView::getChartTitle() const{
    return currentChart->title();
}

void SensorGraphView::buttonLabel(){
    if(toggleSensor->text() == "turn ON"){
        toggleSensor->setText("turn OFF");
        emit turnedOn();
    }
    else{
        toggleSensor->setText("turn ON");
        emit turnedOff();
    }
}

void SensorGraphView::setLabel(QString l){
    label->setText(l);
    mainLayout->addWidget(label, 1,0);
    label->show();
}
