/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QPushButton *geomSetButton;
    QGraphicsView *scene_display;
    QPushButton *openButton;
    QPushButton *saveButton;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(921, 640);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        geomSetButton = new QPushButton(centralWidget);
        geomSetButton->setObjectName(QString::fromUtf8("geomSetButton"));
        geomSetButton->setGeometry(QRect(800, 580, 111, 21));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QString::fromUtf8("scene_display"));
        scene_display->setGeometry(QRect(60, 40, 771, 491));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(60, 560, 80, 24));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(170, 560, 80, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 921, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Scene Graph", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        geomSetButton->setText(QCoreApplication::translate("MainWindow", "Set Geometry", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
