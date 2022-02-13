#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <iostream>

/*
 * Add guassian kernal calculation from radius
 * Skipped derivative stuff for brush strokes
 * Make different brush shapes
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), paint(), ref(nullptr), imageObject(nullptr)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(300);
}

void MainWindow::DisplayQImage(QImage &i)
{
    QPixmap pixmap(QPixmap::fromImage(i));
    graphics_scene.addPixmap(pixmap);
    graphics_scene.setSceneRect(pixmap.rect());
    ui->scene_display->setScene(&graphics_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::tick() {
    graphics_scene.clear();
    graphics_scene.update();
    if (imageObject != nullptr) {
        DisplayQImage(*imageObject);
    } else if (ref != nullptr) {
        DisplayQImage(*ref);
    }
    else {
//        QImage result(512, 512, QImage::Format_RGB32);
//        result.fill(qRgb(rand() % 100, rand() % 100, rand() % 100));
//        DisplayQImage(result);
    }
    graphics_scene.update();
}

void MainWindow::on_openButton_pressed()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    ref = mkU<QImage>();
    ref->load(imagePath);
    imageObject = mkU<QImage>();
    imageObject->load(imagePath);
}

void MainWindow::on_paintButton_pressed() {
    if (ref == nullptr) {
        ref = mkU<QImage>();
        ref->load(QString(":images/Nature1.jpg"));
    }
    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);

    std::list<int> ls = {50, 25, 5, 2};;
    paint.paint(ref.get(), imageObject.get(), ls);
    std::cout << "DONE" << std::endl;
}

void MainWindow::on_saveButton_pressed()
{
    QString imagePath = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    imageObject->save(imagePath);
}

void MainWindow::on_testButton_clicked()
{
    std::list<int> ls = {50, 25, 5, 3};
    uPtr<QImage> ref = mkU<QImage>();
    ref->load(QString(":images/Nature1.jpg"));
    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    std::cout << "BEGIN-------------------------------------------------------------------------------------------" << std::endl;
    paint.paint(ref.get(), imageObject.get(), ls);
    std::cout << imageObject.get()->width() << " " << imageObject.get()->height() << std::endl;
    std::cout << "DONE" << std::endl;
}


void MainWindow::on_continueButton_clicked()
{
    uPtr<QImage> ref = mkU<QImage>();
    ref->load(QString(":images/Nature1.jpg"));
    if (imageObject == nullptr) {
        imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    }
    if (counter > 5) {
        paint.paintLayer(ref.get(), imageObject.get(), counter);
        counter /= 2;

    }
}

