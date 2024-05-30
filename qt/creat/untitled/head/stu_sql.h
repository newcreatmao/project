#ifndef STU_SQL_H
#define STU_SQL_H

#include <QObject>
#include <QSqlTableModel>

struct StuInfo{
    int id;
    QString name;
    int age;
    int grade;
    int uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
};

struct UserInfo{
    QString username;
    QString password;
    QString aut;
};

class stu_sql : public QObject
{
    Q_OBJECT
public:
    explicit stu_sql(QObject *parent = nullptr);
    void Init();
    quint32 getStuCnt();
    QList<StuInfo> getPageStu(quint32 page,quint32 uiCnt);
    bool addStu(StuInfo info);
    bool delStu(int id);
    bool clearStuTable();
    bool UpdateStuInfo(StuInfo info);
    QList<UserInfo> getAllUser();
    bool isExit(QString struser);
    bool changeuserAnt(UserInfo info);
    bool AddUser(UserInfo info);
    bool delUser(QString struserName);
signals:

private:
    QSqlDatabase m_db;
};

#endif // STU_SQL_H
