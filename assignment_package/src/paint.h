#ifndef PAINT_H
#define PAINT_H

#include <QImage>

class Paint
{
public:
    Paint();
    QImage sobelFilter(QImage image);
};

#endif // PAINT_H
