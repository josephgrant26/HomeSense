#include "src/controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    controller c(&w);
    return a.exec();
}


