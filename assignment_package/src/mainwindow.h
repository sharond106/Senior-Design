#pragma once

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QGraphicsScene>
#include <QImage>
#include "mygl.h"
#include <QFileDialog>
#include "smartpointerhelp.h"
#include "paint.h"

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
    QGraphicsScene graphics_scene_for_stroke;

public:
    explicit MainWindow(QWidget *parent = 0);

    void DisplayQImage(QImage &i);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void tick();

    void on_openButton_pressed();

    void on_paintButton_pressed();

    void on_saveButton_pressed();

    void on_strokeButton_pressed();

    void on_clearStrokeButton_pressed();

    void on_noneStyle_pressed();
    void on_impressionistStyle_pressed();
    void on_expressionistStyle_pressed();
    void on_coloristStyle_pressed();
    void on_pointillistStyle_pressed();
    void on_psychedelicStyle_pressed();

private:
    Ui::MainWindow *ui;

    QPixmap image;
    uPtr<QImage> ref;
    uPtr<QImage> imageObject;
    uPtr<QImage> brushImage;
    QGraphicsScene *scene;
    Paint paint;
    QString brushImagePath;

    //Temp variables
    int counter = 50;

    void loadStyleParams();
    std::list<int> loadPaintParams();
    void resizeBrushImage();
};
