#ifndef PAINT_H
#define PAINT_H

#include <QImage>
#include "smartpointerhelp.h"

class Paint
{
public:
    Paint();
    uPtr<QImage> sobelFilter(QImage* image);
};

#endif // PAINT_H
