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
    QGroupBox *parametersGroup;
    QSpinBox *minStrokeLength;
    QSpinBox *maxStrokeLength;
    QSlider *curvatureFilter;
    QCheckBox *hueCheck;
    QCheckBox *saturationCheck;
    QCheckBox *valueCheck;
    QCheckBox *redCheck;
    QCheckBox *greenCheck;
    QCheckBox *blueCheck;
    QSlider *hue;
    QSlider *saturation;
    QSlider *value;
    QSlider *red;
    QSlider *green;
    QSlider *blue;
    QCheckBox *maxStrokeLengthCheck;
    QCheckBox *minStrokeLengthCheck;
    QCheckBox *blurFactorCheck;
    QCheckBox *curvatureFilterCheck;
    QSlider *errorThreshold;
    QCheckBox *errorThresholdCheck;
    QLabel *label_2;
    QSpinBox *numberLayers;
    QSpinBox *smallestRadius;
    QLabel *label;
    QLabel *label_3;
    QComboBox *brushShape;
    QSlider *blurFactor;
    QGroupBox *styleGroup;
    QRadioButton *psychedelicStyle;
    QRadioButton *expressionistStyle;
    QRadioButton *pointillistStyle;
    QRadioButton *impressionistStyle;
    QRadioButton *noneStyle;
    QRadioButton *coloristStyle;
    QGroupBox *groupBox;
    QPushButton *strokeButton;
    QGraphicsView *scene_display_2;
    QPushButton *clearStrokeButton;
    QPushButton *brushImageButton;
    QGraphicsView *scene_display_3;
    QPushButton *clearBrushImageButton;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1384, 729);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QString::fromUtf8("scene_display"));
        scene_display->setGeometry(QRect(60, 40, 771, 621));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(860, 40, 141, 31));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(860, 630, 131, 31));
        paintButton = new QPushButton(centralWidget);
        paintButton->setObjectName(QString::fromUtf8("paintButton"));
        paintButton->setGeometry(QRect(860, 590, 131, 31));
        parametersGroup = new QGroupBox(centralWidget);
        parametersGroup->setObjectName(QString::fromUtf8("parametersGroup"));
        parametersGroup->setGeometry(QRect(860, 90, 271, 451));
        minStrokeLength = new QSpinBox(parametersGroup);
        minStrokeLength->setObjectName(QString::fromUtf8("minStrokeLength"));
        minStrokeLength->setGeometry(QRect(150, 210, 42, 26));
        minStrokeLength->setMinimum(1);
        minStrokeLength->setValue(1);
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
        hueCheck = new QCheckBox(parametersGroup);
        hueCheck->setObjectName(QString::fromUtf8("hueCheck"));
        hueCheck->setGeometry(QRect(10, 270, 131, 24));
        saturationCheck = new QCheckBox(parametersGroup);
        saturationCheck->setObjectName(QString::fromUtf8("saturationCheck"));
        saturationCheck->setGeometry(QRect(10, 300, 131, 24));
        valueCheck = new QCheckBox(parametersGroup);
        valueCheck->setObjectName(QString::fromUtf8("valueCheck"));
        valueCheck->setGeometry(QRect(10, 330, 131, 24));
        redCheck = new QCheckBox(parametersGroup);
        redCheck->setObjectName(QString::fromUtf8("redCheck"));
        redCheck->setGeometry(QRect(10, 360, 131, 24));
        greenCheck = new QCheckBox(parametersGroup);
        greenCheck->setObjectName(QString::fromUtf8("greenCheck"));
        greenCheck->setGeometry(QRect(10, 390, 131, 24));
        blueCheck = new QCheckBox(parametersGroup);
        blueCheck->setObjectName(QString::fromUtf8("blueCheck"));
        blueCheck->setGeometry(QRect(10, 420, 131, 24));
        hue = new QSlider(parametersGroup);
        hue->setObjectName(QString::fromUtf8("hue"));
        hue->setGeometry(QRect(140, 270, 111, 22));
        hue->setMaximum(10);
        hue->setSingleStep(1);
        hue->setValue(0);
        hue->setSliderPosition(0);
        hue->setOrientation(Qt::Horizontal);
        hue->setTickInterval(1);
        saturation = new QSlider(parametersGroup);
        saturation->setObjectName(QString::fromUtf8("saturation"));
        saturation->setGeometry(QRect(140, 300, 111, 22));
        saturation->setMaximum(10);
        saturation->setSingleStep(1);
        saturation->setValue(0);
        saturation->setSliderPosition(0);
        saturation->setOrientation(Qt::Horizontal);
        saturation->setTickInterval(1);
        value = new QSlider(parametersGroup);
        value->setObjectName(QString::fromUtf8("value"));
        value->setGeometry(QRect(140, 330, 111, 22));
        value->setMaximum(10);
        value->setSingleStep(1);
        value->setValue(0);
        value->setSliderPosition(0);
        value->setOrientation(Qt::Horizontal);
        value->setTickInterval(1);
        red = new QSlider(parametersGroup);
        red->setObjectName(QString::fromUtf8("red"));
        red->setGeometry(QRect(140, 360, 111, 22));
        red->setMaximum(10);
        red->setSingleStep(1);
        red->setValue(0);
        red->setSliderPosition(0);
        red->setOrientation(Qt::Horizontal);
        red->setTickInterval(1);
        green = new QSlider(parametersGroup);
        green->setObjectName(QString::fromUtf8("green"));
        green->setGeometry(QRect(140, 390, 111, 22));
        green->setMaximum(10);
        green->setSingleStep(1);
        green->setValue(0);
        green->setSliderPosition(0);
        green->setOrientation(Qt::Horizontal);
        green->setTickInterval(1);
        blue = new QSlider(parametersGroup);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setGeometry(QRect(140, 420, 111, 22));
        blue->setMaximum(10);
        blue->setSingleStep(1);
        blue->setValue(0);
        blue->setSliderPosition(0);
        blue->setOrientation(Qt::Horizontal);
        blue->setTickInterval(1);
        maxStrokeLengthCheck = new QCheckBox(parametersGroup);
        maxStrokeLengthCheck->setObjectName(QString::fromUtf8("maxStrokeLengthCheck"));
        maxStrokeLengthCheck->setGeometry(QRect(10, 240, 131, 24));
        maxStrokeLengthCheck->setChecked(false);
        minStrokeLengthCheck = new QCheckBox(parametersGroup);
        minStrokeLengthCheck->setObjectName(QString::fromUtf8("minStrokeLengthCheck"));
        minStrokeLengthCheck->setGeometry(QRect(10, 210, 141, 24));
        minStrokeLengthCheck->setChecked(false);
        blurFactorCheck = new QCheckBox(parametersGroup);
        blurFactorCheck->setObjectName(QString::fromUtf8("blurFactorCheck"));
        blurFactorCheck->setGeometry(QRect(10, 180, 131, 24));
        curvatureFilterCheck = new QCheckBox(parametersGroup);
        curvatureFilterCheck->setObjectName(QString::fromUtf8("curvatureFilterCheck"));
        curvatureFilterCheck->setGeometry(QRect(10, 150, 131, 24));
        errorThreshold = new QSlider(parametersGroup);
        errorThreshold->setObjectName(QString::fromUtf8("errorThreshold"));
        errorThreshold->setGeometry(QRect(140, 120, 111, 22));
        errorThreshold->setMaximum(1000);
        errorThreshold->setSingleStep(1);
        errorThreshold->setValue(200);
        errorThreshold->setSliderPosition(200);
        errorThreshold->setOrientation(Qt::Horizontal);
        errorThreshold->setTickInterval(1);
        errorThresholdCheck = new QCheckBox(parametersGroup);
        errorThresholdCheck->setObjectName(QString::fromUtf8("errorThresholdCheck"));
        errorThresholdCheck->setGeometry(QRect(10, 120, 131, 24));
        errorThresholdCheck->setChecked(false);
        label_2 = new QLabel(parametersGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 90, 121, 21));
        numberLayers = new QSpinBox(parametersGroup);
        numberLayers->setObjectName(QString::fromUtf8("numberLayers"));
        numberLayers->setGeometry(QRect(140, 90, 42, 26));
        numberLayers->setMinimum(1);
        numberLayers->setMaximum(10);
        numberLayers->setValue(4);
        smallestRadius = new QSpinBox(parametersGroup);
        smallestRadius->setObjectName(QString::fromUtf8("smallestRadius"));
        smallestRadius->setGeometry(QRect(140, 60, 42, 26));
        smallestRadius->setMinimum(1);
        smallestRadius->setValue(2);
        label = new QLabel(parametersGroup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 121, 21));
        label_3 = new QLabel(parametersGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 30, 121, 21));
        brushShape = new QComboBox(parametersGroup);
        brushShape->addItem(QString());
        brushShape->addItem(QString());
        brushShape->setObjectName(QString::fromUtf8("brushShape"));
        brushShape->setGeometry(QRect(140, 30, 80, 26));
        blurFactor = new QSlider(parametersGroup);
        blurFactor->setObjectName(QString::fromUtf8("blurFactor"));
        blurFactor->setGeometry(QRect(140, 180, 111, 22));
        blurFactor->setMaximum(10);
        blurFactor->setSingleStep(1);
        blurFactor->setValue(5);
        blurFactor->setSliderPosition(5);
        blurFactor->setOrientation(Qt::Horizontal);
        blurFactor->setTickInterval(1);
        styleGroup = new QGroupBox(centralWidget);
        styleGroup->setObjectName(QString::fromUtf8("styleGroup"));
        styleGroup->setGeometry(QRect(1140, 90, 231, 211));
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
        noneStyle->setChecked(true);
        coloristStyle = new QRadioButton(styleGroup);
        coloristStyle->setObjectName(QString::fromUtf8("coloristStyle"));
        coloristStyle->setGeometry(QRect(10, 120, 110, 24));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1140, 310, 231, 361));
        strokeButton = new QPushButton(groupBox);
        strokeButton->setObjectName(QString::fromUtf8("strokeButton"));
        strokeButton->setGeometry(QRect(10, 20, 141, 31));
        scene_display_2 = new QGraphicsView(groupBox);
        scene_display_2->setObjectName(QString::fromUtf8("scene_display_2"));
        scene_display_2->setGeometry(QRect(10, 50, 201, 131));
        clearStrokeButton = new QPushButton(groupBox);
        clearStrokeButton->setObjectName(QString::fromUtf8("clearStrokeButton"));
        clearStrokeButton->setGeometry(QRect(130, 150, 81, 31));
        brushImageButton = new QPushButton(groupBox);
        brushImageButton->setObjectName(QString::fromUtf8("brushImageButton"));
        brushImageButton->setGeometry(QRect(10, 190, 141, 31));
        scene_display_3 = new QGraphicsView(groupBox);
        scene_display_3->setObjectName(QString::fromUtf8("scene_display_3"));
        scene_display_3->setGeometry(QRect(10, 220, 201, 131));
        clearBrushImageButton = new QPushButton(groupBox);
        clearBrushImageButton->setObjectName(QString::fromUtf8("clearBrushImageButton"));
        clearBrushImageButton->setGeometry(QRect(130, 320, 81, 31));
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        parametersGroup->raise();
        styleGroup->raise();
        scene_display->raise();
        openButton->raise();
        saveButton->raise();
        paintButton->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1384, 22));
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
        openButton->setText(QCoreApplication::translate("MainWindow", "Upload Source Image", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        paintButton->setText(QCoreApplication::translate("MainWindow", "Generate Painting", nullptr));
        parametersGroup->setTitle(QCoreApplication::translate("MainWindow", "Customize your own parameters", nullptr));
        hueCheck->setText(QCoreApplication::translate("MainWindow", "Hue Jitter", nullptr));
        saturationCheck->setText(QCoreApplication::translate("MainWindow", "Saturation Jitter", nullptr));
        valueCheck->setText(QCoreApplication::translate("MainWindow", "Value Jitter", nullptr));
        redCheck->setText(QCoreApplication::translate("MainWindow", "Red Jitter", nullptr));
        greenCheck->setText(QCoreApplication::translate("MainWindow", "Green Jitter", nullptr));
        blueCheck->setText(QCoreApplication::translate("MainWindow", "Blue Jitter", nullptr));
        maxStrokeLengthCheck->setText(QCoreApplication::translate("MainWindow", "Max stroke length", nullptr));
        minStrokeLengthCheck->setText(QCoreApplication::translate("MainWindow", "Min stroke length", nullptr));
        blurFactorCheck->setText(QCoreApplication::translate("MainWindow", "Blur factor", nullptr));
        curvatureFilterCheck->setText(QCoreApplication::translate("MainWindow", "Curvature filter ", nullptr));
        errorThresholdCheck->setText(QCoreApplication::translate("MainWindow", "Error threshold", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Number of layers", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Smallest brush radius", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Brush shape", nullptr));
        brushShape->setItemText(0, QCoreApplication::translate("MainWindow", "Circle", nullptr));
        brushShape->setItemText(1, QCoreApplication::translate("MainWindow", "Square", nullptr));

        styleGroup->setTitle(QCoreApplication::translate("MainWindow", "Or select a preset style", nullptr));
        psychedelicStyle->setText(QCoreApplication::translate("MainWindow", "Psychedelic", nullptr));
        expressionistStyle->setText(QCoreApplication::translate("MainWindow", "Expressionist", nullptr));
        pointillistStyle->setText(QCoreApplication::translate("MainWindow", "Pointillist", nullptr));
        impressionistStyle->setText(QCoreApplication::translate("MainWindow", "Impressionist", nullptr));
        noneStyle->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        coloristStyle->setText(QCoreApplication::translate("MainWindow", "Colorist Wash", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Optional but upload source image first!", nullptr));
        strokeButton->setText(QCoreApplication::translate("MainWindow", "Upload Stroke Gradient", nullptr));
        clearStrokeButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        brushImageButton->setText(QCoreApplication::translate("MainWindow", "Upload Brush Image", nullptr));
        clearBrushImageButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
