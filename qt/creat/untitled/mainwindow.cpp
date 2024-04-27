#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_dlg.show();
    auto f=[&](){
        this->show();
    };//lambda函数
    connect(&m_dlg,&page_login::sendloginsucce,this,f);//登陆成功跳到主页面
}



MainWindow::~MainWindow()
{
    delete ui;
}
