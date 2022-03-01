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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QGraphicsView *scene_display;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *paintButton;
    QSpinBox *smallestRadius;
    QLabel *label;
    QSpinBox *numberLayers;
    QLabel *label_2;
    QSpinBox *errorThreshold;
    QSpinBox *blurFactor;
    QSlider *opacity;
    QCheckBox *errorThresholdCheck;
    QCheckBox *curvatureFilterCheck;
    QCheckBox *blurFactorCheck;
    QCheckBox *minStrokeLengthCheck;
    QCheckBox *maxStrokeLengthCheck;
    QCheckBox *opacityCheck;
    QComboBox *brushShape;
    QLabel *label_3;
    QGroupBox *parametersGroup;
    QSpinBox *minStrokeLength;
    QSpinBox *maxStrokeLength;
    QSlider *curvatureFilter;
    QGroupBox *styleGroup;
    QRadioButton *psychedelicStyle;
    QRadioButton *expressionistStyle;
    QRadioButton *pointillistStyle;
    QRadioButton *impressionistStyle;
    QRadioButton *noneStyle;
    QRadioButton *coloristStyle;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1355, 640);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QString::fromUtf8("scene_display"));
        scene_display->setGeometry(QRect(60, 40, 771, 541));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(860, 40, 141, 31));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(860, 450, 131, 31));
        paintButton = new QPushButton(centralWidget);
        paintButton->setObjectName(QString::fromUtf8("paintButton"));
        paintButton->setGeometry(QRect(860, 410, 131, 31));
        smallestRadius = new QSpinBox(centralWidget);
        smallestRadius->setObjectName(QString::fromUtf8("smallestRadius"));
        smallestRadius->setGeometry(QRect(1000, 150, 42, 26));
        smallestRadius->setMinimum(1);
        smallestRadius->setValue(2);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(870, 150, 121, 21));
        numberLayers = new QSpinBox(centralWidget);
        numberLayers->setObjectName(QString::fromUtf8("numberLayers"));
        numberLayers->setGeometry(QRect(1000, 180, 42, 26));
        numberLayers->setMinimum(1);
        numberLayers->setMaximum(10);
        numberLayers->setValue(4);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(870, 180, 121, 21));
        errorThreshold = new QSpinBox(centralWidget);
        errorThreshold->setObjectName(QString::fromUtf8("errorThreshold"));
        errorThreshold->setGeometry(QRect(1000, 210, 61, 26));
        errorThreshold->setMaximum(2000);
        errorThreshold->setValue(200);
        blurFactor = new QSpinBox(centralWidget);
        blurFactor->setObjectName(QString::fromUtf8("blurFactor"));
        blurFactor->setGeometry(QRect(1000, 270, 42, 26));
        opacity = new QSlider(centralWidget);
        opacity->setObjectName(QString::fromUtf8("opacity"));
        opacity->setGeometry(QRect(1000, 360, 111, 22));
        opacity->setMaximum(10);
        opacity->setSingleStep(1);
        opacity->setValue(10);
        opacity->setSliderPosition(10);
        opacity->setOrientation(Qt::Horizontal);
        opacity->setTickInterval(1);
        errorThresholdCheck = new QCheckBox(centralWidget);
        errorThresholdCheck->setObjectName(QString::fromUtf8("errorThresholdCheck"));
        errorThresholdCheck->setGeometry(QRect(870, 210, 131, 24));
        errorThresholdCheck->setChecked(false);
        curvatureFilterCheck = new QCheckBox(centralWidget);
        curvatureFilterCheck->setObjectName(QString::fromUtf8("curvatureFilterCheck"));
        curvatureFilterCheck->setGeometry(QRect(870, 240, 131, 24));
        blurFactorCheck = new QCheckBox(centralWidget);
        blurFactorCheck->setObjectName(QString::fromUtf8("blurFactorCheck"));
        blurFactorCheck->setGeometry(QRect(870, 270, 131, 24));
        minStrokeLengthCheck = new QCheckBox(centralWidget);
        minStrokeLengthCheck->setObjectName(QString::fromUtf8("minStrokeLengthCheck"));
        minStrokeLengthCheck->setGeometry(QRect(870, 300, 141, 24));
        minStrokeLengthCheck->setChecked(false);
        maxStrokeLengthCheck = new QCheckBox(centralWidget);
        maxStrokeLengthCheck->setObjectName(QString::fromUtf8("maxStrokeLengthCheck"));
        maxStrokeLengthCheck->setGeometry(QRect(870, 330, 131, 24));
        maxStrokeLengthCheck->setChecked(false);
        opacityCheck = new QCheckBox(centralWidget);
        opacityCheck->setObjectName(QString::fromUtf8("opacityCheck"));
        opacityCheck->setGeometry(QRect(870, 360, 131, 24));
        brushShape = new QComboBox(centralWidget);
        brushShape->addItem(QString());
        brushShape->addItem(QString());
        brushShape->setObjectName(QString::fromUtf8("brushShape"));
        brushShape->setGeometry(QRect(1000, 120, 80, 26));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(870, 120, 121, 21));
        parametersGroup = new QGroupBox(centralWidget);
        parametersGroup->setObjectName(QString::fromUtf8("parametersGroup"));
        parametersGroup->setGeometry(QRect(860, 90, 271, 301));
        minStrokeLength = new QSpinBox(parametersGroup);
        minStrokeLength->setObjectName(QString::fromUtf8("minStrokeLength"));
        minStrokeLength->setGeometry(QRect(150, 210, 42, 26));
        minStrokeLength->setMinimum(1);
        minStrokeLength->setValue(7);
        maxStrokeLength = new QSpinBox(parametersGroup);
        maxStrokeLength->setObjectName(QString::fromUtf8("maxStrokeLength"));
        maxStrokeLength->setGeometry(QRect(150, 240, 42, 26));
        maxStrokeLength->setMinimum(1);
        maxStrokeLength->setValue(12);
        curvatureFilter = new QSlider(parametersGroup);
        curvatureFilter->setObjectName(QString::fromUtf8("curvatureFilter"));
        curvatureFilter->setGeometry(QRect(140, 150, 111, 22));
        curvatureFilter->setMaximum(10);
        curvatureFilter->setSingleStep(1);
        curvatureFilter->setValue(10);
        curvatureFilter->setSliderPosition(10);
        curvatureFilter->setOrientation(Qt::Horizontal);
        curvatureFilter->setTickInterval(1);
        styleGroup = new QGroupBox(centralWidget);
        styleGroup->setObjectName(QString::fromUtf8("styleGroup"));
        styleGroup->setGeometry(QRect(1140, 90, 171, 301));
        psychedelicStyle = new QRadioButton(styleGroup);
        psychedelicStyle->setObjectName(QString::fromUtf8("psychedelicStyle"));
        psychedelicStyle->setGeometry(QRect(10, 180, 110, 24));
        expressionistStyle = new QRadioButton(styleGroup);
        expressionistStyle->setObjectName(QString::fromUtf8("expressionistStyle"));
        expressionistStyle->setGeometry(QRect(10, 90, 110, 24));
        pointillistStyle = new QRadioButton(styleGroup);
        pointillistStyle->setObjectName(QString::fromUtf8("pointillistStyle"));
        pointillistStyle->setGeometry(QRect(10, 150, 110, 24));
        impressionistStyle = new QRadioButton(styleGroup);
        impressionistStyle->setObjectName(QString::fromUtf8("impressionistStyle"));
        impressionistStyle->setGeometry(QRect(10, 60, 110, 24));
        noneStyle = new QRadioButton(styleGroup);
        noneStyle->setObjectName(QString::fromUtf8("noneStyle"));
        noneStyle->setGeometry(QRect(10, 30, 110, 24));
        coloristStyle = new QRadioButton(styleGroup);
        coloristStyle->setObjectName(QString::fromUtf8("coloristStyle"));
        coloristStyle->setGeometry(QRect(10, 120, 110, 24));
        MainWindow->setCentralWidget(centralWidget);
        parametersGroup->raise();
        styleGroup->raise();
        scene_display->raise();
        openButton->raise();
        saveButton->raise();
        paintButton->raise();
        smallestRadius->raise();
        label->raise();
        numberLayers->raise();
        label_2->raise();
        errorThreshold->raise();
        blurFactor->raise();
        opacity->raise();
        errorThresholdCheck->raise();
        curvatureFilterCheck->raise();
        blurFactorCheck->raise();
        minStrokeLengthCheck->raise();
        maxStrokeLengthCheck->raise();
        opacityCheck->raise();
        brushShape->raise();
        label_3->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1355, 26));
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
        openButton->setText(QCoreApplication::translate("MainWindow", "Upload Image", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        paintButton->setText(QCoreApplication::translate("MainWindow", "Generate Painting", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Smallest brush radius", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of layers", nullptr));
        errorThresholdCheck->setText(QCoreApplication::translate("MainWindow", "Error threshold", nullptr));
        curvatureFilterCheck->setText(QCoreApplication::translate("MainWindow", "Curvature filter ", nullptr));
        blurFactorCheck->setText(QCoreApplication::translate("MainWindow", "Blur factor", nullptr));
        minStrokeLengthCheck->setText(QCoreApplication::translate("MainWindow", "Min stroke length", nullptr));
        maxStrokeLengthCheck->setText(QCoreApplication::translate("MainWindow", "Max stroke length", nullptr));
        opacityCheck->setText(QCoreApplication::translate("MainWindow", "Opacity", nullptr));
        brushShape->setItemText(0, QCoreApplication::translate("MainWindow", "Circle", nullptr));
        brushShape->setItemText(1, QCoreApplication::translate("MainWindow", "Square", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Brush shape", nullptr));
        parametersGroup->setTitle(QCoreApplication::translate("MainWindow", "Customize your own parameters", nullptr));
        styleGroup->setTitle(QCoreApplication::translate("MainWindow", "Or select a preset style", nullptr));
        psychedelicStyle->setText(QCoreApplication::translate("MainWindow", "Psychedelic", nullptr));
        expressionistStyle->setText(QCoreApplication::translate("MainWindow", "Expressionist", nullptr));
        pointillistStyle->setText(QCoreApplication::translate("MainWindow", "Pointillist", nullptr));
        impressionistStyle->setText(QCoreApplication::translate("MainWindow", "Impressionist", nullptr));
        noneStyle->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        coloristStyle->setText(QCoreApplication::translate("MainWindow", "Colorist Wash", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
