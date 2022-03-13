#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <iostream>

/*
 * Add guassian kernal calculation from radius
 * Skipped derivative stuff for brush strokes
 * Make parameters on ui and implement functionality
 * See if timer can work properly
 * support upload pngs
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), paint(), ref(nullptr), imageObject(nullptr), brushImage(nullptr)
{
    ui->setupUi(this);
    ui->scene_display->setWindowTitle(QString("Painting Generator"));
//    imageObject = mkU<QImage>();
//    imageObject->load(QString(":images/apple.jpg"));
//    imageObject = paint.gaussianBlur(imageObject.get());

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(300);
}

void MainWindow::DisplayQImage(QImage &i)
{
    QPixmap pixmap(QPixmap::fromImage(i));
    graphics_scene.addPixmap(pixmap);
    graphics_scene.setSceneRect(pixmap.rect());

    ui->scene_display->setScene(&graphics_scene);
    ui->scene_display->fitInView(pixmap.rect(), Qt::KeepAspectRatio);
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
    }

    else {
//        QImage result(512, 512, QImage::Format_RGB32);
//        result.fill(qRgb(rand() % 100, rand() % 100, rand() % 100));
//        DisplayQImage(result);
    }
    graphics_scene.update();
}

std::list<int> MainWindow::loadPaintParams() {
    paint.brush = static_cast<BrushShape>(ui->brushShape->currentIndex());

    if (ui->errorThresholdCheck->isChecked()) {
        paint.errorThreshold = ui->errorThreshold->value();
    } else {
        paint.errorThreshold = 200.;
    }

    if (ui->minStrokeLengthCheck->isChecked()) {
        paint.minStrokeLength = ui->minStrokeLength->value();
    } else {
        paint.minStrokeLength = 1.;
    }

    if (ui->maxStrokeLengthCheck->isChecked()) {
        paint.maxStrokeLength = ui->maxStrokeLength->value();
    } else {
        paint.maxStrokeLength = -1.;
    }

//    if (ui->opacityCheck->isChecked()) {
//        paint.opacity = ui->opacity->value() / 10.;
//    } else {
//        paint.opacity = 1.0;
//    }

    if (ui->curvatureFilterCheck->isChecked()) {
        paint.curvatureFilter = ui->curvatureFilter->value() / 10.;
    } else {
        paint.curvatureFilter = 1.0;
    }

    if (brushImage != nullptr && brushImage->width() > 0) {
        paint.brushImage = mkU<QImage>(*this->brushImage.get());
    } else {
        paint.brushImage = nullptr;
    }

    // Create list of brush sizes from largest to smallest'
    int smallestR = ui->smallestRadius->value();
    int numLayers = ui->numberLayers->value();
    std::list<int> l = {smallestR};
    auto it = l.begin();
    for (int i = 0; i < numLayers - 1; i++) {
        l.insert(it, l.front() * 2);
        it = l.begin();
    }

    return l;
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

void MainWindow::on_strokeButton_pressed()
{
    graphics_scene.clear();
    if (ref == nullptr || ref->width() <= 0) {
        std::cout << "Upload source image first" << std::endl;
        return;
    }
    brushImagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    resizeBrushImage();

    // display it in the viewer
    QPixmap pixmap(QPixmap::fromImage(*brushImage));
    graphics_scene_for_stroke.addPixmap(pixmap);
    graphics_scene_for_stroke.setSceneRect(pixmap.rect());

    ui->scene_display_2->setScene(&graphics_scene_for_stroke);
    ui->scene_display_2->fitInView(pixmap.rect(), Qt::KeepAspectRatio);
}

void MainWindow::resizeBrushImage() {
    brushImage = mkU<QImage>();
    brushImage->load((brushImagePath));
    *brushImage = brushImage->scaled(ref->width(), ref->height(), Qt::KeepAspectRatioByExpanding);
    *brushImage = brushImage->copy((brushImage->width() / 2.) - (ref->width() / 2.),
                                   (brushImage->height() / 2.) - (ref->height() / 2.),
                                   ref->width(), ref->height());
}

void MainWindow::on_clearStrokeButton_pressed() {
    brushImage = mkU<QImage>();
    graphics_scene_for_stroke.clear();
    ui->scene_display_2->setScene(&graphics_scene_for_stroke);
}

void MainWindow::on_paintButton_pressed() {
    if (ref == nullptr) {
        ref = mkU<QImage>();
        ref->load(QString(":images/Nature1.jpg"));
    }
    imageObject = mkU<QImage>(ref->width(), ref->height(),  QImage::Format_RGB32);

    if (brushImage != nullptr && brushImage->width() > 0) {
        resizeBrushImage();
    }

    std::list<int> ls = loadPaintParams();

    // SOMETIMES PIXEL COLORS ARE NEVER SET IF THERE'S ONLY 1 LAYER
    imageObject->fill(QColor(0, 255, 0));

    // this still isn't showing up in layers with the timer
    for (int r: ls) {
       paint.paintLayer(ref.get(), imageObject.get(), r);
    }
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

