#ifndef STU_SQL_H
#define STU_SQL_H

#include <QObject>

class stu_sql : public QObject
{
    Q_OBJECT
public:
    explicit stu_sql(QObject *parent = nullptr);

signals:
};

#endif // STU_SQL_H
