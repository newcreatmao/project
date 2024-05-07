#include "../head/mainwindow.h"
#include "../head/stu_sql.h"
#include <QSqlDatabase>
#include <QApplication>
#include <qdebug.h>
#include <QMessageBox>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    stu_sql sql;
    return a.exec();
}


// QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
// db.setHostName("192.168.142.131");
// db.setPort(3306);
// db.setDatabaseName("student");
// db.setUserName("root");
// db.setPassword("123456");
// bool ok = db.open();
// if (ok){
//     qDebug()<<"SECCES";
// }
// else {
//     qDebug()<<"error open database because"<<db.lastError().text();
// }
