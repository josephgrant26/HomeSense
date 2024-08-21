QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp    \
        src/controller/controller.cpp \
        src/model/airConditioner.cpp \
        src/model/ariQualitySensor.cpp \
        src/model/motionSensor.cpp \
        src/model/proxAlarm.cpp \
        src/model/sensor.cpp \
        src/model/temperatureSensor.cpp \
        src/model/waterSensor.cpp \
        src/view/mainwindow.cpp \
        src/view/sensorpanel.cpp \
        src/view/view.cpp

HEADERS += \
    src/controller/controller.h \
    src/model/airConditioner.h \
    src/model/airQualitySensor.h \
    src/model/motionSensor.h \
    src/model/proxAlarm.h \
    src/model/sensor.h \
    src/model/temperatureSensor.h \
    src/model/waterSensor.h \
    src/view/mainwindow.h \
    src/view/sensorpanel.h \
    src/view/view.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/logo.png
