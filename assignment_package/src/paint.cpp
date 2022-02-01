#include "paint.h"

Paint::Paint()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

QImage Paint::makeImage()
{
    QImage result(512, 512, QImage::Format_RGB32);
    result.fill(qRgb(0.f, 255.f, 255.f));
    return result;
}
