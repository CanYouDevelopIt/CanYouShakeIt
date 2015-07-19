/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *start;
    QPushButton *setParameters;
    QListWidget *listJoueurs;
    QTextEdit *nouveauJoueur;
    QLabel *enterNameLabel;
    QListWidget *listScores;
    QLabel *labelScore;
    QLabel *labelSelectJoueur;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(535, 496);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(330, 100, 150, 46));
        setParameters = new QPushButton(centralWidget);
        setParameters->setObjectName(QStringLiteral("setParameters"));
        setParameters->setGeometry(QRect(10, 100, 150, 46));
        listJoueurs = new QListWidget(centralWidget);
        listJoueurs->setObjectName(QStringLiteral("listJoueurs"));
        listJoueurs->setGeometry(QRect(10, 170, 231, 231));
        nouveauJoueur = new QTextEdit(centralWidget);
        nouveauJoueur->setObjectName(QStringLiteral("nouveauJoueur"));
        nouveauJoueur->setGeometry(QRect(10, 50, 231, 41));
        enterNameLabel = new QLabel(centralWidget);
        enterNameLabel->setObjectName(QStringLiteral("enterNameLabel"));
        enterNameLabel->setGeometry(QRect(10, 10, 231, 25));
        listScores = new QListWidget(centralWidget);
        listScores->setObjectName(QStringLiteral("listScores"));
        listScores->setGeometry(QRect(290, 210, 231, 191));
        labelScore = new QLabel(centralWidget);
        labelScore->setObjectName(QStringLiteral("labelScore"));
        labelScore->setGeometry(QRect(296, 180, 221, 20));
        labelSelectJoueur = new QLabel(centralWidget);
        labelSelectJoueur->setObjectName(QStringLiteral("labelSelectJoueur"));
        labelSelectJoueur->setGeometry(QRect(330, 49, 151, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 535, 21));
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
        start->setText(QApplication::translate("MainWindow", "Start", 0));
        setParameters->setText(QApplication::translate("MainWindow", "Param\303\250tres", 0));
        enterNameLabel->setText(QString());
        labelScore->setText(QApplication::translate("MainWindow", "Top scores", 0));
        labelSelectJoueur->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
