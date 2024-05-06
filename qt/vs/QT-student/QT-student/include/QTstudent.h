#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTstudent.h"

class QTstudent : public QMainWindow
{
    Q_OBJECT

public:
    QTstudent(QWidget *parent = nullptr);
    ~QTstudent();

private:
    Ui::QTstudentClass ui;
};
