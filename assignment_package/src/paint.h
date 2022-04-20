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


enum BrushShape { CIRCLE, SQUARE, CUSTOM };

class Paint
{

public:

    int minStrokeLength = 1;
    int maxStrokeLength = -1;
    float errorThreshold = 200.;
    bool useThreads = true;
    int threadCount = 8;
    BrushShape brush = CIRCLE;
    float opacity = 1.0;
    float curvatureFilter = 1.;
    float blurFactor = 1.;
    uPtr<QImage> gradientImage = nullptr;
    uPtr<QImage> brushImage = nullptr;
    float hueJitter = 0.;
    float satJitter = 0.;
    float valueJitter = 0.;
    float redJitter = 0.;
    float greenJitter = 0.;
    float blueJitter = 0.;
    float brushImageSize = 0.;
    bool paintedFirstLayer = false;

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

    void applyPaintCustom(Stroke* stroke, QImage* canvas, QImage* brushImage);

    void paintLayer(QImage* reference, QImage* canvas, int brushSize);

    void paint(QImage* reference, QImage* canvas, std::list<int> brushSizes);
};

#endif // PAINT_H
