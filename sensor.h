#include <iostream>
class Sensor{

private:

    bool isInit;

public:
    Sensor();
    virtual double getReading()=0;
    void initialize();

};

#