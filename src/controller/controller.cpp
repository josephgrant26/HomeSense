#include "controller.h"

Controller::Controller(QObject* parent): QObject(parent), home(new MainWindow()), sensorPanel(new SensorPanel()), addSensor(new AddSensor()),
    graphView(new SensorGraphView()), sensorGraph(nullptr), simulator(nullptr), sensors(new vector<Sensor*>), savePath(""),
    view(new View(home, addSensor, sensorPanel, graphView)){

    savePath= getStandardSaveLocation();

    //Controller connections
    connect(this, &Controller::refreshGraphs, this, [this] {
        if(simulator){
            graphView->buttonLabel();
            saveData();
        }
        else
           saveData();

        openWindow(home);});

    //View connections:
    connect(view, &View::goHome,  this, [this] {
        if(dynamic_cast<SensorGraphView*>(view->getCurrentWidget())){
            if(simulator)
                graphView->buttonLabel();
        }
        openWindow(home);});

    //mainWindow connections:
    connect(home, &MainWindow::openSensorPanel, this, [this] {openWindow(sensorPanel);});
    connect(home, &MainWindow::sensorClicked, this, &Controller::openSensorGraph);

    //sensorPanel connections:
    connect(sensorPanel, &SensorPanel::appendFile, this, [this] {addData(fileToDoc(fileDialog())); InitHomeScreen();});
    connect(sensorPanel, &SensorPanel::newSensor, this, [this] {openWindow(addSensor);});

    //addSensor connections:
    connect(addSensor, &AddSensor::currentIndexChanged, this, &Controller::displayValueDesc);
    connect(addSensor, &AddSensor::submitValue, this, [this] {addSensor->displayAQM(createAQMVec());});
    connect(addSensor, &AddSensor::submitSensor, this,  &Controller::createNewSensor);

    //sensorGraphView connections:
    connect(graphView, &SensorGraphView::turnedOn, this, [this] {openSimluator(sensorGraph->title());});
    connect(graphView, &SensorGraphView::turnedOff, this, &Controller::closeSimulator);
    connect(graphView, &SensorGraphView::changedValues, this, &Controller::updateData);
    connect(graphView, &SensorGraphView::removedSensor, this, [this] {removeSensor(graphView->getChartTitle());});

    if(sensors->empty()){
        if(!initData()) sensors= nullptr;
    }

    createView();

}

Controller::~Controller(){
    delete home;
    delete sensorPanel;
    delete addSensor;
    delete graphView;
    delete sensorGraph;
    delete simulator;
    if (sensors) {
        for (auto sensor : *sensors) {
            delete sensor;
        }
        delete sensors;
    }
    delete view;
}

QJsonDocument Controller::saveDataDoc() const{
    QFile saveData (savePath);
    saveData.open(QIODevice::ReadOnly);
    QByteArray fileData = saveData.readAll();
    saveData.close();
    QJsonDocument saveDoc = QJsonDocument::fromJson(fileData);
    return saveDoc;
}

Sensor* Controller::getSensor(QString name) const{

    for(auto it = sensors->cbegin(); it != sensors->cend(); ++it){
        if((*it)->getName() == name.toStdString()){ return *it; }

    }
    return nullptr;
}

void Controller::createView(){

    InitHomeScreen();

    view->showMaximized();

}

void Controller::InitHomeScreen(){

    view->setHome(createQLabelVector());

}


QVector<QPushButton*> Controller::createQLabelVector(){
    QVector<QPushButton*> tmp;

    home->removeSensors();
    for(vector<Sensor*>::const_iterator it = sensors->cbegin(); it != sensors->cend(); ++it){

        QPushButton* btn = new QPushButton(QString::fromStdString((*it)->getName()));
        tmp.push_back(btn);
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
    return vec;

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
    QMessageBox error;
    error.critical(view, "Error", "Coudln't open file");
    return false;

}

bool Controller::saveData() const{

    QFile file(savePath);

    QJsonArray array;

    for(auto it = sensors->cbegin(); it != sensors->cend(); ++it){
        QJsonObject obj;
        obj["name"] = QString::fromStdString((*it)->getName());
        if(dynamic_cast<TemperatureSensor*>(*it)){                          //TemperatureSensor & AirConditioner
            auto ob = dynamic_cast<TemperatureSensor*>(*it);
            obj["lastTemperature"] = (ob)->getReading();
            if(dynamic_cast<AirConditioner*>(*it)){
                obj["type"] = "AirConditioner";
                obj["TargetTemp"] = dynamic_cast<AirConditioner*>(*it)->getTargetTemp();
            }
            else obj["type"] = "TemperatureSensor";

        }

        if(dynamic_cast<AirQualitySensor*>(*it)){                           //AirQualitySensor
            auto ob = dynamic_cast<AirQualitySensor*>(*it);
            std::unordered_map<string,double> tmp = ob->getAllLimits();
            QJsonObject umap, umap1;

            for(auto it = tmp.cbegin(); it != tmp.cend(); ++it){
                umap[QString::fromStdString((*it).first)]= (*it).second;
                umap1[QString::fromStdString((*it).first)]= (ob->getReading((*it).first));
            }
            obj["Chemical&Limits"] = umap;
            obj["type"] = "AirQualitySensor";
            obj["Chemical_latestValues"] = umap1;
        }

        if(dynamic_cast<MotionSensor*>(*it)){                               //MotionSensor & ProxAlarm
            auto ob = dynamic_cast<MotionSensor*>(*it);
            obj["radius"] = (ob)->getCalibration();
            if(dynamic_cast<ProxAlarm*>(*it))
                obj["type"] = "ProxAlarm";
            else obj["type"] = "MotionSensor";
        }

        if(dynamic_cast<WaterSensor*>(*it)){                                //WaterSensor
            auto ob = dynamic_cast<WaterSensor*>(*it);
            obj["leak"] = ob->getReading();
            obj["tollerance"] = (ob)->getTollerance();
            obj["type"] = "WaterSensor";
        }

        array.push_back(obj);

    }

    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(array);

    if(!file.isOpen()){
        QMessageBox error;
        error.critical(view, "Error", "Couldn't open save file");
         return false;
    }
    else{
        file.write(doc.toJson());
        file.close();
        return true;
    }
    QMessageBox error;
    error.critical(view, "Error", "Unexpected error");
    return false;
}

bool Controller::addData(QJsonDocument doc){
    QJsonArray newDataArray = doc.array();
    QJsonDocument saveDoc = saveDataDoc();
    QJsonArray saveDataArray = saveDoc.array();

    //check name clashes new file vs current file
    for(auto it = saveDataArray.cbegin(); it != saveDataArray.cend(); ++it){
        QJsonObject obj = (*it).toObject();
        for(auto kt = newDataArray.cbegin(); kt != newDataArray.cend(); ++kt){
            QJsonObject bjo = (*kt).toObject();
            if(obj["name"] == bjo["name"]){
                QMessageBox error;
                error.critical(view, "Error", "New file musn't have the same sensor names as the save file");
                return false;
            }
        }
    }

    if(newDataArray.isEmpty()) return false;
    for(auto it = newDataArray.cbegin(); it != newDataArray.cend(); ++it){
        saveDataArray.push_back(*it);
    }
    QFile file(savePath);
    file.open(QIODevice::WriteOnly);
    saveDoc = QJsonDocument(saveDataArray);

    if(!file.isOpen()){
        QMessageBox error;
        error.critical(view, "Error", "Couldn't open save file");
        return false;
    }

    else{
        file.write(saveDoc.toJson());
        file.close();
        loadData(saveDataDoc());
        InitHomeScreen();
        return true;
    }

    return false;



}

QString Controller::getStandardSaveLocation() const{
    QString fileName, saveLocation, filePath;
    fileName = "sample.json";
    saveLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(saveLocation);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    filePath = saveLocation + "/" + fileName;

    QFile file(filePath);

    if (!file.exists())
        file.open(QIODevice::WriteOnly);

    return filePath;
}

bool Controller::removeSensor(QString name){
    bool found = false;

    if(simulator) graphView->buttonLabel();
    for(auto it = sensors->begin(); it != sensors->end();){
        if(QString::fromStdString((*it)->getName()) == name){
            found = true;
            delete (*it);
            sensors->erase((it));
            break;
        }
        else{
            ++it;
        }
    }
    InitHomeScreen();
    saveData();
    if(!found){
        QMessageBox error;
        error.critical(view, "Error", "Coudln't remove sensor");
    }
    return found;
}

void Controller::openSimluator(QString n){

    Sensor* s = getSensor(n);
    simulator = new Simulator(s,sensorGraph, graphView);

}

void Controller::closeSimulator(){
    if(simulator){
        saveData();
        simulator->resetLabels();
        delete simulator;
        simulator = nullptr;
        sensorGraph->clearGraph();
    }
}

void Controller::updateData(){

    string name = sensorGraph->title().toStdString();
    vector<tuple<string,double>> v;
    v = graphView->newValues();
    for(auto it= sensors->cbegin(); it != sensors->cend(); ++it){
        if((*it)->getName() == name){
            if(dynamic_cast<AirConditioner*>(*it)){
                dynamic_cast<AirConditioner*>(*it)->setTargetTemp(get<1>((*v.begin())));;
            }
            else if(dynamic_cast<MotionSensor*>(*it)){
                dynamic_cast<MotionSensor*>(*it)->calibrate(get<1>((*v.begin())));;
            }
            else if(dynamic_cast<WaterSensor*>(*it)){
                dynamic_cast<WaterSensor*>(*it)->setLeakTollerance(get<1>((*v.begin())));;
            }
            else if(dynamic_cast<AirQualitySensor*>(*it)){
                auto vec = dynamic_cast<AirQualitySensor*>(*it)->getAllLimits();
                for(auto kt = vec.begin(); kt != vec.end(); ++kt){
                    for(auto jt = v.begin(); jt != v.end(); ++jt){
                        if((*kt).first == get<0>(*jt))
                            dynamic_cast<AirQualitySensor*>(*it)->setValue((*kt).first, get<1>(*jt));
                    }
                }
            }
        }
    }
    emit refreshGraphs();
}

bool Controller::loadData(QJsonDocument doc) {
    if(sensors) sensors->clear();
    QJsonArray array = doc.array();
    for(auto it = array.cbegin(); it != array.cend(); ++it){
        QJsonObject obj = it->toObject();
        if(obj["type"] == "TemperatureSensor"){
            TemperatureSensor* tmp = new TemperatureSensor(obj["name"].toString().toStdString());
            sensors->push_back(tmp);
        }
        else if(obj["type"] == "ProxAlarm"){
            ProxAlarm* tmp = new ProxAlarm(obj["name"].toString().toStdString(), obj["radius"].toDouble());
            sensors->push_back(tmp);
        }
        else if(obj["type"] == "AirConditioner"){
            AirConditioner* tmp = new AirConditioner(obj["name"].toString().toStdString(), obj["lastTemperature"].toInt());
            tmp->setTargetTemp(obj["TargetTemp"].toDouble());
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
            QJsonObject chems, chems1;
            chems = obj["Chemical&Limits"].toObject();
            chems1 = obj["Chemical_latestValues"].toObject();
            for(auto it = chems.constBegin(); it != chems.constEnd(); ++it){
                double val = chems1.find(it.key()).value().toDouble();
                umap[it.key().toStdString()] = std::make_tuple(val, it.value().toDouble());
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
    addSensor->hideAQM();
    if(type == "Motion Sensor" || type == "Proximity Alarm"){ addSensor->setValueDesc("set Range (in metres)"); addSensor->showValueWidget(); addSensor->hideValueSubmit(); }
    else if(type == "Water Leaks Sensor"){ addSensor->setValueDesc("Leakage threshold (in mL)"); addSensor->showValueWidget(); addSensor->hideValueSubmit(); }
    else if(type == "Air Quality Sensors"){ addSensor->setValueDesc("How many chemicals?"); addSensor->showValueWidget();}
    else if(type == "Air Conditioner"){ addSensor->setValueDesc("Set Temperature Target"); addSensor->showValueWidget(); addSensor->hideValueSubmit(); }
    else{ addSensor->removeValueWidgets();}
}

bool Controller::createNewSensor(){
    QString type = addSensor->getSensorType();
    Sensor* tmp;
    for(auto it = sensors->cbegin(); it != sensors->cend(); ++it){
        if((*it)->getName() == addSensor->getSensorName().toStdString()){
            QMessageBox error;
            error.critical(view, "Error", "Sensor name clashes with existing sensors");
            return false;
        }
    }

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
        tmp = new AirConditioner(addSensor->getSensorName().toStdString(), addSensor->getValue());
    }
    else{
        QMessageBox error;
        error.critical(view, "Error", "Unexpected error in sensor creation");
        return false;
    }

    sensors->push_back(tmp);

    InitHomeScreen();

    saveData();

    return true;

}

void Controller::openSensorGraph(QString name){

    graphView->unloadChart();
    Sensor* s = getSensor(name);
    if(sensorGraph) delete sensorGraph;
    QVector<QString> vec;
    QVector<QString> values;
    double axisMin =0;
    double axisMax =100;

    if(dynamic_cast<TemperatureSensor*>(s)){
        vec.push_back("temperatura(Celsius)");
        if(dynamic_cast<AirConditioner*>(s))
            values.push_back("target temperatura");

        axisMin = -20;
        axisMax = 50;
    }
    else if(dynamic_cast<MotionSensor*>(s)){
        vec.push_back("MovimentoCatturato(m)");
        values.push_back("Raggio d'azione");
        axisMin = 0;
        axisMax = dynamic_cast<MotionSensor*>(s)->getCalibration();
    }
    else if(dynamic_cast<WaterSensor*>(s)){
        vec.push_back("Perdita(Ml)");
        values.push_back("limite perdita");
    }
    else if(dynamic_cast<AirQualitySensor*>(s)){
        AirQualitySensor* q = dynamic_cast<AirQualitySensor*>(s);
        auto vals = q->getAllLimits();
        for(auto it = vals.cbegin(); it != vals.cend(); ++it){
            vec.push_back(QString::fromStdString(it->first));
            values.push_back(QString::fromStdString(it->first));
        }
    }
    sensorGraph = new SensorGraph(name,vec, axisMin, axisMax);

    graphView->loadChart(sensorGraph, values);

    if(dynamic_cast<TemperatureSensor*>(s))
        graphView->setLabel("");
    else if(dynamic_cast<MotionSensor*>(s))
        graphView->setLabel("Nessun Movimento");
    else if(dynamic_cast<AirConditioner*>(s))
        graphView->setLabel("currently heating");
    else
        graphView->setLabel("alarm is OFF");

    view->setCurrentWidget(graphView);

}

