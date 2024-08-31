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

    QString getSensorName() const;
    double getValue() const;
    QString getSensorType() const;

    void setValueDesc(QString);
    void removeValueWidgets();
    void showValueWidget();
    void displayAQM(const QVector<tuple<QLineEdit*, QDoubleSpinBox*>>&);  //displays the airQUalityMaker vector
    void hideAQM();
    const std::unordered_map<std::string, tuple<double,double>> getAQMValues();

signals:
    void submitValue();
    void submitSensor();
    void currentIndexChanged();

};

#endif // ADDSENSOR_H
