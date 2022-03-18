#ifndef STROKEWORKER_H
#define STROKEWORKER_H
#include <QRunnable>
#include <QString>
#include <QMutex>
#include <QImage>
#include "glm/mat3x3.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include "glm/trigonometric.hpp"
#include "stroke.h"
#include "smartpointerhelp.h"
#include "helpers.h"


class StrokeWorker : public QRunnable
{
public:
    int maxStrokeLength, minStrokeLength;
    float curvatureFilter;
    int x, y, grid;

    float errorThreshold;
    QMutex* mutex;
    QImage* reference;
    QImage* blurred;
    QImage* brushImage;

    std::vector<uPtr<Stroke>>* zbuf;

    StrokeWorker();
    StrokeWorker(int x, int y, int grid, QMutex* mutex, QImage* reference, QImage* blurred, QImage* brushImage,
                 int maxStrokeLength, int minStrokeLength, float curvatureFilter, std::vector<uPtr<Stroke>>* zbuf);

    void run() override;
};

#endif // STROKEWORKER_H
