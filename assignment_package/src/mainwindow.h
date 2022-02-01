#pragma once

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QGraphicsScene>
#include <QImage>
#include "mygl.h"
#include <QFileDialog>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTimer timer;
    QImage rendered_image;
    QGraphicsScene graphics_scene;

public:
    explicit MainWindow(QWidget *parent = 0);

    void DisplayQImage(QImage &i);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void tick();

    void on_openButton_pressed();

    void on_saveButton_pressed();

private:
    Ui::MainWindow *ui;

    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
};
