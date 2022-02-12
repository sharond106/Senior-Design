#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <iostream>

/*
 * Clean UI and make buttons usable
 * Fix vertical strokes
 * Add guassian kernal calculation from radius
 * Skipped derivative stuff for brush strokes
 * Randomly sort per layer
 * Make different brush shapes
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), paint(), ref(), imageObject()
{
    ui->setupUi(this);

    uPtr<QImage> ref = mkU<QImage>();
    ref->load(QString(":images/Grid.jpg"));
//    imageObject = paint.GaussianBlur(imageObject.get());
//    imageObject = paint.sobelFilter(imageObject.get());

//    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    //paint.paint(ref.get(), imageObject.get(), std::list<int>(100));

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
    } else {
        QImage result(512, 512, QImage::Format_RGB32);
        result.fill(qRgb(rand() % 100, rand() % 100, rand() % 100));
        DisplayQImage(result);
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

    uPtr<QImage> ref = mkU<QImage>();
    ref->load(imagePath);

    //imageObject->load(imagePath);
    //DisplayQImage(*imageObject);

    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    paint.paint(ref.get(), imageObject.get(), std::list<int>(100));
}

void MainWindow::on_saveButton_pressed()
{
    QString imagePath = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    *imageObject = image.toImage();

    imageObject->save(imagePath);
}

void MainWindow::on_testButton_clicked()
{
    std::list<int> ls = {50, 25, 5};
    uPtr<QImage> ref = mkU<QImage>();
    ref->load(QString(":images/swirly2.jpg"));
    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    std::cout << "BEGIN-------------------------------------------------------------------------------------------" << std::endl;
    paint.paint(ref.get(), imageObject.get(), ls);
//    imageObject = paint.sobelFilter(ref.get());
    std::cout << imageObject.get()->width() << " " << imageObject.get()->height() << std::endl;
    std::cout << "DONE" << std::endl;

}


void MainWindow::on_continueButton_clicked()
{
    uPtr<QImage> ref = mkU<QImage>();
    ref->load(QString(":images/Grid.jpg"));
    if (imageObject == nullptr) {
        imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);
    }
    if (counter > 5) {
        paint.paintLayer(ref.get(), imageObject.get(), counter);
        counter /= 2;

    }
}

