/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblTitle;
    QPushButton *btnAdd;
    QPushButton *btnMonth;
    QPushButton *btnSearch;
    QPushButton *btnRemove;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *btnUpgrade;
    QPushButton *btnDowngrade;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(552, 343);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblTitle = new QLabel(centralWidget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(200, 10, 221, 21));
        btnAdd = new QPushButton(centralWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(200, 200, 151, 41));
        btnMonth = new QPushButton(centralWidget);
        btnMonth->setObjectName(QStringLiteral("btnMonth"));
        btnMonth->setGeometry(QRect(20, 250, 151, 41));
        btnSearch = new QPushButton(centralWidget);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setGeometry(QRect(20, 200, 151, 41));
        btnRemove = new QPushButton(centralWidget);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));
        btnRemove->setGeometry(QRect(380, 200, 151, 41));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 40, 531, 111));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(200, 160, 151, 31));
        btnUpgrade = new QPushButton(centralWidget);
        btnUpgrade->setObjectName(QStringLiteral("btnUpgrade"));
        btnUpgrade->setGeometry(QRect(200, 250, 151, 41));
        btnDowngrade = new QPushButton(centralWidget);
        btnDowngrade->setObjectName(QStringLiteral("btnDowngrade"));
        btnDowngrade->setGeometry(QRect(380, 250, 151, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 552, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lblTitle->setText(QApplication::translate("MainWindow", "Wholesale Club Membership Info", 0));
        btnAdd->setText(QApplication::translate("MainWindow", "Add Member", 0));
        btnMonth->setText(QApplication::translate("MainWindow", "View Month", 0));
        btnSearch->setText(QApplication::translate("MainWindow", "Search Member", 0));
        btnRemove->setText(QApplication::translate("MainWindow", "Remove Member", 0));
        btnUpgrade->setText(QApplication::translate("MainWindow", "Check Upgrade", 0));
        btnDowngrade->setText(QApplication::translate("MainWindow", "Check Downgrade", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
