/********************************************************************************
** Form generated from reading UI file 'a14.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A14_H
#define UI_A14_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_a14Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *a14Class)
    {
        if (a14Class->objectName().isEmpty())
            a14Class->setObjectName(QString::fromUtf8("a14Class"));
        a14Class->resize(600, 400);
        menuBar = new QMenuBar(a14Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        a14Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(a14Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        a14Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(a14Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        a14Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(a14Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        a14Class->setStatusBar(statusBar);

        retranslateUi(a14Class);

        QMetaObject::connectSlotsByName(a14Class);
    } // setupUi

    void retranslateUi(QMainWindow *a14Class)
    {
        a14Class->setWindowTitle(QCoreApplication::translate("a14Class", "a14", nullptr));
    } // retranslateUi

};

namespace Ui {
    class a14Class: public Ui_a14Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A14_H
