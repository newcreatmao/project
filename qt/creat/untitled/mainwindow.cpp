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


    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);

    QStringList name;
    name<<"学生管理系统";
    QTreeWidgetItem*pf= new QTreeWidgetItem(ui->treeWidget,name);
    ui->treeWidget->addTopLevelItem(pf);

    name.clear();
    name<<"学生管理";
    QTreeWidgetItem*p1= new QTreeWidgetItem(pf,name);
    name.clear();
    name<<"管理员管理";
    QTreeWidgetItem*p2= new QTreeWidgetItem(pf,name);

    pf->addChild(p1);
    pf->addChild(p2);
    ui->treeWidget->expandAll();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
