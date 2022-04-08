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
    void addAngle(float theta);
    float radius;
    int randomKey;
    QColor color;
    std::vector<std::pair<int, int>> points;
    //angle at each point in radians. Computed using gradient
    std::vector<float> angles;
};

#endif // STROKE_H
