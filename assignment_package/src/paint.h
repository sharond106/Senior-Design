#ifndef PAINT_H
#define PAINT_H

#include <QImage>
#include <QTimer>

class Paint : public QObject
{
    Q_OBJECT
private:
    QTimer timer;
    QImage rendered_image;
public:
    Paint();
    QImage makeImage();
    void DisplayQImage(QImage &i);
};

#endif // PAINT_H
