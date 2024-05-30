#include "../head/page_login.h"
#include "ui_page_login.h"

page_login::page_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_login)
{
    ui->setupUi(this);
}

page_login::~page_login()
{
    delete ui;
}

void page_login::on_bin_login_clicked()
{
    //数据库查找账号密码

    //失败就提示

    //成功进入界面
    emit sendloginsucce();
}


void page_login::on_bin_exit_clicked()//退出
{
    exit(0);
}

