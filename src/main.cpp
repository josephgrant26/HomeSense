#include <QApplication>
#include "src/controller/controller.h"
#include <QDebug>
//#include "src/model/mod"
//#include "src/view/view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c;
    return a.exec();
}


