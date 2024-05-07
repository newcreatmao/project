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
    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(nullptr, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));

}


QSqlError stu_sql::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                 const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("Browser%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("Browser%1").arg(cCount));
    }

    return err;
}
