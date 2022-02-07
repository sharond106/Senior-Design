#ifndef STROKE_H
#define STROKE_H

#include <QImage>
#include <list>

class Stroke
{
public:
    Stroke();
    Stroke(int radius, QColor color, std::pair<int, int> start);
    void addPoint(int x, int y);
    float radius;
    QColor color;
    std::list<std::pair<int, int>> points;
};

#endif // STROKE_H
