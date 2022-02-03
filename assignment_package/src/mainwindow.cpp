#include "mainwindow.h"
#include <ui_mainwindow.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(1000);
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

    imageObject = new QImage();
    imageObject->load(imagePath);

    DisplayQImage(*imageObject);
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
