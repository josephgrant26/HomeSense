#include <iostream>
class Sensor{

private:

    bool isInit;

public:
    Sensor(bool=false);
    virtual double getReading()=0;
    void initialize();

};

#