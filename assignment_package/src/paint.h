#ifndef PAINT_H
#define PAINT_H

#include "smartpointerhelp.h"
#include "stroke.h"
#include "math.h"
#include "blurworker.h"
#include "strokeworker.h"
#include "helpers.h"
#include "glm/vec3.hpp"
#include "glm/mat3x3.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <QThreadPool>
#include <QImage>


enum BrushShape { CIRCLE, SQUARE };

class Paint
{
public:
//    const float kernel [121] = {0.006849,	0.007239,	0.007559,	0.007795,	0.007941,	0.00799,	0.007941,	0.007795,	0.007559,	0.007239,	0.006849,
//                                0.007239,	0.007653,	0.00799,	0.00824,	0.008394,	0.008446,	0.008394,	0.00824,	0.00799,	0.007653,	0.007239,
//                                0.007559,	0.00799,	0.008342,	0.008604,	0.008764,	0.008819,	0.008764,	0.008604,	0.008342,	0.00799,	0.007559,
//                                0.007795,	0.00824,	0.008604,	0.008873,	0.009039,	0.009095,	0.009039,	0.008873,	0.008604,	0.00824,	0.007795,
//                                0.007941,	0.008394,	0.008764,	0.009039,	0.009208,	0.009265,	0.009208,	0.009039,	0.008764,	0.008394,	0.007941,
//                                0.00799,    0.008446,	0.008819,	0.009095,	0.009265,	0.009322,	0.009265,	0.009095,	0.008819,	0.008446,	0.00799,
//                                0.007941,	0.008394,	0.008764,	0.009039,	0.009208,	0.009265,	0.009208,	0.009039,	0.008764,	0.008394,	0.007941,
//                                0.007795,	0.00824,	0.008604,	0.008873,	0.009039,	0.009095,	0.009039,	0.008873,	0.008604,	0.00824,	0.007795,
//                                0.007559,	0.00799,	0.008342,	0.008604,	0.008764,	0.008819,	0.008764,	0.008604,	0.008342,	0.00799,	0.007559,
//                                0.007239,	0.007653,	0.00799,	0.00824,	0.008394,	0.008446,	0.008394,	0.00824,	0.00799,	0.007653,	0.007239,
//                                0.006849,	0.007239,	0.007559,	0.007795,	0.007941,	0.00799,	0.007941,	0.007795,	0.007559,	0.007239,	0.006849};

    int minStrokeLength = 7;
    int maxStrokeLength = 12;      // pass these in through constructor eventually
    float errorThreshold = 200.;
    bool useThreads = true;
    int threadCount = 8;
    BrushShape brush = CIRCLE;
    float opacity = 1.0;
    float curvatureFilter = 1.;
    uPtr<QImage> brushImage = nullptr;

    Paint();

    float gaussEquation(float x, float y, float stdev);

    //Generate Kernel based on a size input
    std::vector<float> generateKernel(int span, float stdev);

    // For visual debugging
    uPtr<QImage> sobelFilter(QImage* image);

    //Blur
    uPtr<QImage> gaussianBlur(QImage* image, int size);

    bool inCircle(int x, int y, int centerX, int centerY, float r);

    bool checkShape(int x, int y, int centerX, int centerY, float r);

    void applyPaint(Stroke* stroke, QImage* canvas);

    void paintLayer(QImage* reference, QImage* canvas, int brushSize);

    void paint(QImage* reference, QImage* canvas, std::list<int> brushSizes);
};

#endif // PAINT_H
