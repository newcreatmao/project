#include "../include/QTstudent.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTstudent w;
    w.show();
    return a.exec();
}
