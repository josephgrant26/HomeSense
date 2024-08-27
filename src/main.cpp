#include <QApplication>
#include "src/controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c;
    return a.exec();
}


