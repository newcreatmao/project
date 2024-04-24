#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
//异常的接口声明
void func()throw() //只允许 func中抛出 double类型异常 ,如果throw中写() 代表不允许抛出异常
{
   // throw 1;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try
    {
        func();
    }
    catch(int)
    {
        qDebug() << "int类型异常捕获";
    }
    catch(double)
    {
        qDebug() << "double类型异常捕获";
    }

    return a.exec();
}
