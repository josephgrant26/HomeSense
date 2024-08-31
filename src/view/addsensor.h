#ifndef ADDSENSOR_H
#define ADDSENSOR_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QVector>
#include <tuple>

using std::tuple;
using std::get;

class AddSensor: public QWidget
{
    Q_OBJECT
private:
    QGridLayout* mainLayout;
    QComboBox* sensorTypes;
    QLineEdit* sensorName;
    QPushButton* submit;

    //type specific
    QLabel* valueDesc;
    QDoubleSpinBox* value;
    QPushButton* valueSubmit;
    QVector<tuple<QLineEdit*, QDoubleSpinBox*>>* airQualityMaker;    //aka AQM

public:
    AddSensor(QWidget* =0);
    ~AddSensor();
    QString getSensorName() const;
    QString getSensorType() const;

    //logic for modifiable sensor attributes
    double getValue() const;
    void setValueDesc(QString);
    void removeValueWidgets();
    void hideValueSubmit();
    void showValueWidget();
    void displayAQM(const QVector<tuple<QLineEdit*, QDoubleSpinBox*>>&);  //displays the airQUalityMaker vector
    void hideAQM();
    const std::unordered_map<std::string, tuple<double,double>> getAQMValues() const;

signals:
    void submitValue();
    void submitSensor();
    void currentIndexChanged();

};

#endif // ADDSENSOR_H
