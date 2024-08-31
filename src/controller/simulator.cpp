#include "simulator.h"

Simulator::Simulator(Sensor* s, SensorGraph* g, SensorGraphView* v): sensor(s), sensorGraph(g),
    graphView(v), timer(new QTimer(this)), elapsed(new QElapsedTimer()){

    connect(timer, &QTimer::timeout, this, &Simulator::generateValues);

    timer->start(2000);
    elapsed->start();

}

void Simulator::generateValues(){

    int time = elapsed->elapsed() / 1000;
    sensor->initialize();   //turns on sensor
    //handle TemperatureSensor new data:
    if(dynamic_cast<TemperatureSensor*>(sensor)){
        double val = QRandomGenerator::global()->bounded(-20,50);
        dynamic_cast<TemperatureSensor*>(sensor)->setValue(val);
        sensorGraph->updateSeries("temperatura(Celsius)", time,val);

        if(dynamic_cast<AirConditioner*>(sensor)){
            AirConditioner* tmp = dynamic_cast<AirConditioner*>(sensor);
            double val1 = 0;
            if(tmp->cooling())
                val1 = QRandomGenerator::global()->bounded(static_cast<int>(-20), static_cast<int>(sensorGraph->getCurrrentValue("temperatura(Celsius)")));
            if(!tmp->cooling())
                val1 = QRandomGenerator::global()->bounded(static_cast<int>(sensorGraph->getCurrrentValue("temperatura(Celsius)")), static_cast<int>(50));
            sensorGraph->updateSeries("temperatura(Celsius)", time,val1);

            if(val > tmp->getTargetTemp()){
                dynamic_cast<AirConditioner*>(sensor)->cool();
                graphView->setLabel("Raffreddando");
            }
            if(val < dynamic_cast<AirConditioner*>(sensor)->getTargetTemp()){
                dynamic_cast<AirConditioner*>(sensor)->heat();
                graphView->setLabel("Riscaldando");
            }
        }
    }

    //handle MotionSensor new data:
    else if(dynamic_cast<MotionSensor*>(sensor)){

        bool capt = QRandomGenerator::global()->bounded(2); //decide ad ogni chiamata se e' stato catturato del movimento
        double val =0;
        MotionSensor* tmp = dynamic_cast<MotionSensor*>(sensor);

        if(capt){
            val = QRandomGenerator::global()->bounded((dynamic_cast<MotionSensor*>(sensor)->getCalibration()));
            graphView->setLabel("Rilevato movimento a distanza:");
        }
        if(!capt){
            graphView->setLabel("Nessun Movimento");
        }
        tmp->setMovement();
        tmp->setValue(val);
        sensorGraph->updateSeries("MovimentoCatturato(m)", time, val);

        if(dynamic_cast<ProxAlarm*>(sensor))
            dynamic_cast<ProxAlarm*>(sensor)->toggleAlarm();
    }

    //handle WaterSensor new data:
    else if(dynamic_cast<WaterSensor*>(sensor)){

        double val = QRandomGenerator::global()->bounded(0,100);
        dynamic_cast<WaterSensor*>(sensor)->setValue(val);
        sensorGraph->updateSeries("Perdita(Ml)", time, val);

        if(val > dynamic_cast<WaterSensor*>(sensor)->getTollerance()){
            dynamic_cast<WaterSensor*>(sensor)->toggleAlarm();
            graphView->setLabel("Allarme accesa!!");
        }
        if(val < dynamic_cast<WaterSensor*>(sensor)->getTollerance()){
            dynamic_cast<WaterSensor*>(sensor)->toggleAlarm();
            graphView->setLabel("Allarme spenta");
        }

    }

    //handle AirQualitySensor new data:
    else if(dynamic_cast<AirQualitySensor*>(sensor)){

        auto vals = dynamic_cast<AirQualitySensor*>(sensor)->getAllLimits();

        for(auto it = vals.cbegin(); it != vals.cend(); ++it){
            double val = QRandomGenerator::global()->bounded(0,100);

            sensorGraph->updateSeries(it->first, time, val);

            dynamic_cast<AirQualitySensor*>(sensor)->setValue(it->first,val);
        }

        if(dynamic_cast<AirQualitySensor*>(sensor)->getReading() > 0)
            graphView->setLabel("Allarme accesa!!");
        if(dynamic_cast<AirQualitySensor*>(sensor)->getReading() == 0)
            graphView->setLabel("Allarme spenta");

    }

}

string Simulator::getCurrentSensor() const{
    return sensor->getName();
}

void Simulator::resetLabels() const{
    if(dynamic_cast<MotionSensor*>(sensor))
        graphView->setLabel("Nessun Movimento");
    else if(dynamic_cast<AirConditioner*>(sensor))
        graphView->setLabel("Raffreddando");
    else if(dynamic_cast<WaterSensor*>(sensor))
        graphView->setLabel("Allarme spenta");
    else if(dynamic_cast<AirQualitySensor*>(sensor))
        graphView->setLabel("Allarme spenta");
}
