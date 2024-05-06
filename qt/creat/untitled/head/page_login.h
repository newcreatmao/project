#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>

namespace Ui {
class page_login;
}

class page_login : public QWidget
{
    Q_OBJECT

public:
    explicit page_login(QWidget *parent = nullptr);
    ~page_login();

private slots:
    void on_bin_login_clicked();

    void on_bin_exit_clicked();
signals:
    void sendloginsucce();
private:
    Ui::page_login *ui;
};

#endif // PAGE_LOGIN_H
