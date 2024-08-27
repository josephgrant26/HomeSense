#include "addsensor.h"

AddSensor::AddSensor(QWidget* parent): QWidget(parent), mainLayout(new QGridLayout(this)),
    sensorTypes(new QComboBox(this)), sensorName(new QLineEdit("sensor name", this)), submit(new QPushButton("create sensor", this)),
    valueDesc(new QLabel(this)), value(new QDoubleSpinBox(this)), valueSubmit(new QPushButton("confirm value", this)),
    airQualityMaker(new QVector<tuple<QLineEdit*,QDoubleSpinBox*>>){

    connect(submit, &QPushButton::clicked, this, &AddSensor::submitSensor);
    connect(valueSubmit, &QPushButton::clicked, this, &AddSensor::submitValue);
    connect(sensorTypes, &QComboBox::currentIndexChanged, this, &AddSensor::currentIndexChanged);

    sensorTypes->addItem("Select sensor type");
    sensorTypes->addItem("Motion Sensor");
    sensorTypes->addItem("Proximity Alarm");
    sensorTypes->addItem("Air Conditioner");
    sensorTypes->addItem("Air Quality Sensors");
    sensorTypes->addItem("Temperature Sensor");
    sensorTypes->addItem("Water Leaks Sensor");



    mainLayout->addWidget(sensorTypes, 0,0);
    mainLayout->addWidget(sensorName, 1,0);
    mainLayout->addWidget(value, 2,1);
    mainLayout->addWidget(valueSubmit, 2,2);
    mainLayout->addWidget(submit, 3,0);

    setLayout(mainLayout);
}

QString AddSensor::getSensorName() const{ return sensorName->text() ;}

double AddSensor::getValue()const{ return value->value(); }

QString AddSensor::getSensorType() const{ return sensorTypes->currentText(); }

void AddSensor::setValueDesc(QString text){

    mainLayout->removeWidget(valueDesc);
    valueDesc->clear();
    valueDesc->setText(text);
    mainLayout->addWidget(valueDesc, 2,0);
}

void AddSensor::removeValueWidgets(){
    value->hide();
    valueSubmit->hide();
    valueDesc->hide();
    mainLayout->update();
}

void AddSensor::removeValueSubmit(){ valueSubmit->hide(); }

void AddSensor::displayAQM(const QVector<tuple<QLineEdit *, QDoubleSpinBox *> > & v){

    int i=4;
    mainLayout->removeWidget(submit);
    for(auto it = v.cbegin(); it != v.cend(); ++it){
        mainLayout->addWidget(get<0>(*it), i,0);
        mainLayout->addWidget(get<1>(*it), i, 1);
        ++i;

        airQualityMaker->push_back(std::make_tuple(get<0>(*it),get<1>(*it)));
    }

    mainLayout->addWidget(submit, i,0);


}

const std::unordered_map<std::string, tuple<double, double> > AddSensor::getAQMValues(){
    std::unordered_map<std::string, tuple<double, double> > umap;
    for(auto it = airQualityMaker->cbegin(); it != airQualityMaker->cend(); ++it){
        umap.insert({get<0>(*it)->text().toStdString(), std::make_tuple(0,get<1>(*it)->value())});
    }
    return umap;
}

