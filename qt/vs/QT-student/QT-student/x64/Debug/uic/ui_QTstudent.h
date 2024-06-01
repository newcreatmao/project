/********************************************************************************
** Form generated from reading UI file 'QTstudent.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSTUDENT_H
#define UI_QTSTUDENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTstudentClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTstudentClass)
    {
        if (QTstudentClass->objectName().isEmpty())
            QTstudentClass->setObjectName("QTstudentClass");
        QTstudentClass->resize(600, 400);
        centralWidget = new QWidget(QTstudentClass);
        centralWidget->setObjectName("centralWidget");
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 130, 75, 24));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(150, 170, 24, 22));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(230, 220, 98, 20));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(300, 190, 82, 20));
        QTstudentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTstudentClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 33));
        QTstudentClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTstudentClass);
        mainToolBar->setObjectName("mainToolBar");
        QTstudentClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTstudentClass);
        statusBar->setObjectName("statusBar");
        QTstudentClass->setStatusBar(statusBar);

        retranslateUi(QTstudentClass);

        QMetaObject::connectSlotsByName(QTstudentClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTstudentClass)
    {
        QTstudentClass->setWindowTitle(QCoreApplication::translate("QTstudentClass", "QTstudent", nullptr));
        pushButton->setText(QCoreApplication::translate("QTstudentClass", "PushButton", nullptr));
        toolButton->setText(QCoreApplication::translate("QTstudentClass", "...", nullptr));
        radioButton->setText(QCoreApplication::translate("QTstudentClass", "RadioButton", nullptr));
        checkBox->setText(QCoreApplication::translate("QTstudentClass", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTstudentClass: public Ui_QTstudentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSTUDENT_H
