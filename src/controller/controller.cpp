#include "controller.h"

Controller::Controller(QObject* parent): QObject(parent), home(new MainWindow()), sensorPanel(new SensorPanel()), addSensor(new AddSensor()),
    sensors(new vector<Sensor*>), savePath("saveData.json"), view(new View(home, addSensor, sensorPanel)){

    //View connections:
    connect(view, &View::newSavePath, this, [this] {savePath = fileDialog(); loadData(fileToDoc(savePath)); InitHomeScreen();});

    //mainWindow connections:
    connect(home, &MainWindow::openSensorPanel, this, [this] {openWindow(sensorPanel);});

    //sensorPanel connections:
    connect(sensorPanel, &SensorPanel::openHome, this, [this] {openWindow(home);});
    connect(sensorPanel, &SensorPanel::appendFile, this, [this] {addData(fileToDoc(fileDialog())); InitHomeScreen();});
    connect(sensorPanel, &SensorPanel::newSensor, this, [this] {openWindow(addSensor);});

    //addSensor connections:
    connect(addSensor, &AddSensor::currentIndexChanged, this, &Controller::displayValueDesc);
    connect(addSensor, &AddSensor::submitValue, this, [this] {addSensor->displayAQM(createAQMVec());});
    connect(addSensor, &AddSensor::submitSensor, this,  &Controller::createNewSensor);

    if(sensors->empty()){
        if(!initData()) sensors= nullptr;
    }

    createView();

}

QJsonDocument Controller::saveDataDoc(){
    QFile saveData (savePath);
    saveData.open(QIODevice::ReadOnly);
    QByteArray fileData = saveData.readAll();
    saveData.close();
    QJsonDocument saveDoc = QJsonDocument::fromJson(fileData);
    return saveDoc;
}

void Controller::createView(){

    InitHomeScreen();

    view->show();

}

void Controller::InitHomeScreen(){

    view->setHome(createQLabelVector());

}


QVector<QPushButton*> Controller::createQLabelVector(){

    QVector<QPushButton*> tmp;
    if(sensors){
        for(vector<Sensor*>::const_iterator it = sensors->cbegin(); it != sensors->cend(); ++it){
            QPushButton* btn = new QPushButton(QString::fromStdString((*it)->getName()));
            tmp.push_back(btn);
        }
    }
    return tmp;
}

QVector<tuple<QLineEdit *, QDoubleSpinBox *> > Controller::createAQMVec(){

    QVector<tuple<QLineEdit *, QDoubleSpinBox *> > vec;

    for(int i = 0; i < addSensor->getValue(); ++i){
        QLineEdit* tmp = new QLineEdit("chemical name");
        QDoubleSpinBox * tmp2 = new QDoubleSpinBox();
        vec.push_back(std::make_tuple(tmp,tmp2));
    }
    qDebug("lmao");
    return vec;

}

bool Controller::newSensor(){
    return true;

}

bool Controller::initData(){

    QFile file(savePath);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray fileData = file.readAll();
        QJsonDocument doc = (QJsonDocument::fromJson(fileData));
        file.close();
        loadData(doc);
        return true;
    }
    return false;

}

bool Controller::saveData() const{

    QString filePath = savePath;

    QFile file(filePath);


    QJsonArray array;
    if(!sensors) return false;
    for(auto it = sensors->cbegin(); it != sensors->cend(); ++it){
        QJsonObject obj;
        obj["name"] = QString::fromStdString((*it)->getName());
        if(dynamic_cast<TemperatureSensor*>(*it)){                          //TemperatureSensor & AirConditioner
            auto ob = dynamic_cast<TemperatureSensor*>(*it);
            obj["lastTemperature"] = QString::number((ob)->getReading());
            if(dynamic_cast<AirConditioner*>(*it))
                obj["type"] = "AirConditioner";
            else obj["type"] = "TemperatureSensor";

        }
        if(dynamic_cast<AirQualitySensor*>(*it)){                           //AirQualitySensor
            auto ob = dynamic_cast<AirQualitySensor*>(*it);
            std::unordered_map<string,double> tmp = ob->getAllLimits();
            QJsonObject umap;
            for(auto it = tmp.cbegin(); it != tmp.cend(); ++it){
                umap[QString::fromStdString((*it).first)]= (*it).second;
            }
            obj["Chemical&Limits"] = umap;
            obj["type"] = "AirQualitySensor";
        }
        if(dynamic_cast<MotionSensor*>(*it)){                               //MotionSensor & ProxAlarm
            auto ob = dynamic_cast<MotionSensor*>(*it);
            obj["radius"] = QString::number((ob)->getCalibration());
            if(dynamic_cast<ProxAlarm*>(*it))
                obj["type"] = "ProxAlarm";
            else obj["type"] = "MotionSensor";
        }
        if(dynamic_cast<WaterSensor*>(*it)){                                //WaterSensor
            auto ob = dynamic_cast<WaterSensor*>(*it);
            obj["leak"] = QString::number(ob->getReading());
            obj["tollerance"] = QString::number((ob)->getTollerance());
            obj["type"] = "WaterSensor";
        }

        array.push_back(obj);

    }



    if(array.isEmpty()){
        return false;
    }

    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(array);

    if(!file.isOpen()){
        return false;
    }

    else{
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}

bool Controller::addData(QJsonDocument doc){
    QJsonArray newDataArray = doc.array();
    QJsonDocument saveDoc = saveDataDoc();
    QJsonArray saveDataArray = saveDoc.array();
    if(newDataArray.isEmpty()) return false;

    for(auto it = newDataArray.cbegin(); it != newDataArray.cend(); ++it){
        saveDataArray.push_back(*it);
    }

    QFile file(savePath);
    file.open(QIODevice::WriteOnly);
    saveDoc = QJsonDocument(saveDataArray);

    if(!file.isOpen()){
        return false;
    }

    else{
        file.write(saveDoc.toJson());
        file.close();
        loadData(saveDataDoc());                                  //WHAT IF I'M UPLOADING THE SAME SAVEDATA FILE OR A FILE WITH THE SAME SENSORS??!
        InitHomeScreen();
        return true;
    }
    return false;



}

bool Controller::loadData(QJsonDocument doc) {
    if(sensors) sensors->clear();
    QJsonArray array = doc.array();
    for(auto it = array.cbegin(); it != array.cend(); ++it){
        QJsonObject obj = it->toObject();
        if(obj["type"] == "TemperatureSensor"){
            TemperatureSensor* tmp = new TemperatureSensor(obj["name"].toString().toStdString());
            sensors->push_back(tmp);
            //delete tmp;
        }
        else if(obj["type"] == "ProxAlarm"){
            ProxAlarm* tmp = new ProxAlarm(obj["name"].toString().toStdString(), obj["radius"].toDouble());
            sensors->push_back(tmp);
        }
        else if(obj["type"] == "AirConditioner"){
            AirConditioner* tmp = new AirConditioner(obj["name"].toString().toStdString(), obj["lastTemperature"].toInt());
            sensors->push_back(tmp);
        }
        else if(obj["type"] == "WaterSensor"){
            WaterSensor* tmp = new WaterSensor(obj["name"].toString().toStdString(), obj["leak"].toDouble());
            tmp->setLeakTollerance(obj["tollerance"].toDouble());
            sensors->push_back(tmp);

        }
        else if(obj["type"] == "MotionSensor"){
            MotionSensor* tmp = new MotionSensor(obj["name"].toString().toStdString(), obj["radius"].toDouble());
            sensors->push_back(tmp);
        }
        else if(obj["type"] == "AirQualitySensor"){
            unordered_map<string, tuple<double,double>> umap;
            QJsonObject chems;
            chems = obj["Chemical&Limits"].toObject();
            for(auto it = chems.constBegin(); it != chems.constEnd(); ++it){
                umap[it.key().toStdString()] = std::make_tuple(0.0, it.value().toDouble());
            }

            if(umap.empty())    return false;

            AirQualitySensor* tmp = new AirQualitySensor(umap, obj["name"].toString().toStdString());
            sensors->push_back(tmp);
        }
    }

    return true;

}

void Controller::openWindow(QWidget* w){ view->setCurrentWidget(w); }

QString Controller::fileDialog(){
    QString fileName = QFileDialog::getOpenFileName(sensorPanel, "Open JSON File", "", "JSON Files (*.json);;All Files (*)");

    if(fileName.isEmpty()){
        QMessageBox error;
        error.critical(sensorPanel, "Unexpected Behaviour", "No file Selected");
        return QString();
    }

    return fileName;
}

QJsonDocument Controller::fileToDoc(QString path){

    QString fileName = path;

    if(fileName.isEmpty()){
        QMessageBox error;
        error.critical(sensorPanel, "Unexpected Behaviour", "No file Selected");
        return QJsonDocument();
    }

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) throw std::runtime_error("Could not open file");

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    return doc;

}

void Controller::displayValueDesc(){
    QString type = addSensor->getSensorType();
    if(type == "Motion Sensor" || type == "Proximity Alarm"){ addSensor->setValueDesc("set Range (in metres)"); addSensor->removeValueSubmit(); }
    else if(type == "Water Leaks Sensor"){ addSensor->setValueDesc("Leakage threshold (in mL)"); addSensor->removeValueSubmit(); }
    else if(type == "Air Quality Sensors") addSensor->setValueDesc("How many chemicals?");
    else{ addSensor->removeValueWidgets();}
}

bool Controller::createNewSensor(){
    QString type = addSensor->getSensorType();
    Sensor* tmp;
    if(type == "Motion Sensor"){
        tmp = new MotionSensor(addSensor->getSensorName().toStdString(),addSensor->getValue());
    }
    else if(type == "Proximity Alarm"){
        tmp = new ProxAlarm(addSensor->getSensorName().toStdString(), addSensor->getValue());
    }
    else if(type == "Water Leaks Sensor"){
        tmp = new WaterSensor(addSensor->getSensorName().toStdString(), addSensor->getValue());
    }
    else if(type == "Air Quality Sensors"){
        tmp = new AirQualitySensor(addSensor->getAQMValues(), addSensor->getSensorName().toStdString());
    }
    else if(type == "Temperature Sensor"){
        tmp = new TemperatureSensor(addSensor->getSensorName().toStdString());
    }
    else if(type == "Air Conditioner"){
        tmp = new AirConditioner(addSensor->getSensorName().toStdString());
    }
    else return false;

    sensors->push_back(tmp);

    InitHomeScreen();

    saveData();

    return true;

}

