#ifndef STU_SQL_H
#define STU_SQL_H

#include <QObject>
#include <QSqlTableModel>

class stu_sql : public QObject
{
    Q_OBJECT
public:
    explicit stu_sql(QObject *parent = nullptr);
    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                            const QString &user, const QString &passwd, int port);
signals:
};

#endif // STU_SQL_H
