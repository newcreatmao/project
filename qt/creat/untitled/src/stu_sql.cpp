#include "../head/stu_sql.h"

#include <QAction>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextEdit>
#include <QTimer>
#include <QSqlDatabase>

stu_sql::stu_sql(QObject *parent)
    : QObject{parent}
{

}

void stu_sql::Init()
{
    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(nullptr, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("192.168.142.131");
    m_db.setPort(3306);
    m_db.setDatabaseName("student");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    bool ok = m_db.open();
    if (!ok) {
        QMessageBox::warning(nullptr, tr("Unable to open database"),
                             tr("An error occurred while "
                                "opening the connection: %1") .arg(m_db.lastError().text()));
        return;
    }
    else{
        QMessageBox::information(nullptr, tr("static"),tr("link success"));
    }
}

quint32 stu_sql::getStuCnt()
{
    QSqlQuery sql(m_db);
    quint32 count;
    sql.exec("select count(id) from student;");
    while(sql.next()){
        count=sql.value(0).toUInt();
    }
    return count;
}

QList<StuInfo> stu_sql::getPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);
    QString str=QString("select * from student order by id limit %1 offset %2;")
        .arg(uiCnt)
        .arg(page*uiCnt);
    sql.exec(str);
    StuInfo info;
    while(sql.next()){
        info.id=sql.value(0).toUInt();
        info.name=sql.value(1).toString();
        info.age=sql.value(2).toUInt();
        info.grade=sql.value(3).toUInt();
        info.uiclass=sql.value(4).toUInt();
        info.studentid=sql.value(5).toUInt();
        info.phone=sql.value(6).toString();
        info.wechat=sql.value(7).toString();
        l.push_back(info);
    }
    return l;
}

bool stu_sql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into student valuse(null,'%1',%2,%3,%4,%5,'%6','%7');")
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.studentid)
                         .arg(info.phone)
                         .arg(info.wechat);
    return sql.exec(strSql);
}

bool stu_sql::delStu(int id)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from student where id=%1;").arg(id));
}

bool stu_sql::clearStuTable()
{
    QSqlQuery sql(m_db);
    return sql.exec("delete from student;");
}

bool stu_sql::UpdateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update student set name='%1',age=%2,grade=%3,class=%4,studentid=%5,phone='%6',wechat='%7' where id=%8;")
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.studentid)
                         .arg(info.phone)
                         .arg(info.wechat)
                         .arg(info.id);
    bool ret= sql.exec(strSql);
    QSqlError e =sql.lastError();
    if(e.isValid()){
        qDebug()<<e.text();
    }
    return ret;
}

QList<UserInfo> stu_sql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);
    sql.exec("select * from username;");
    UserInfo info;
    while(sql.next()){
        info.username=sql.value(0).toString();
        info.password=sql.value(1).toString();
        info.aut=sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool stu_sql::isExit(QString struser)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("select * from username where username=%1;").arg(struser));
}

bool stu_sql::changeuserAnt(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update username set password='%2',aut='%3',where username=%1;")
                         .arg(info.username)
                         .arg(info.password)
                         .arg(info.aut);
    bool ret= sql.exec(strSql);
    QSqlError e =sql.lastError();
    if(e.isValid()){
        qDebug()<<e.text();
    }
    return ret;
}

bool stu_sql::AddUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into username valuse('%1','%2','%3');")
                         .arg(info.username)
                         .arg(info.password)
                         .arg(info.aut);
    return sql.exec(strSql);
}

bool stu_sql::delUser(QString struserName)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delect from username where username=%1;").arg(struserName));
}

