#ifndef PAINT_H
#define PAINT_H

#include <QImage>
#include "smartpointerhelp.h"
#include "stroke.h"
#include "glm/vec3.hpp"
#include "math.h"
#include <QThreadPool>
#include "blurworker.h"

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

    int minStrokeLength = 1;
    int maxStrokeLength = -1;
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

    // Returns gradient orientation of sobel filtered image at x, y
    // [-pi, pi]
    float gradient(int x, int y, QImage* image);

    uPtr<QImage> gaussianBlur(QImage* image, int size);

    //Returns true if the coordinates defined by x and y is out of bounds for the image
    bool outOfBounds(int x, int y, QImage* image);    

    // Caps c to [0, 255]
    int cap(int c);

    // Returns QColor in range [0, 255]
    QColor getColor(QImage* image, int x, int y);

    // Returns RGB [0-255]
    glm::vec3 colorAt(int x, int y, QImage* image);

    bool inCircle(int x, int y, int centerX, int centerY, float r);

    bool checkShape(int x, int y, int centerX, int centerY, float r);

    uPtr<Stroke> paintStroke(int x, int y, int radius, QImage* reference, QImage* canvas);

    // Returns x, y of largest error and the error of the area
    glm::vec3 areaError(int x, int y, int grid, QImage* reference, QImage* canvas);

    void applyPaint(Stroke* stroke, QImage* canvas);

    void paintLayer(QImage* reference, QImage* canvas, int brushSize);

    void paint(QImage* reference, QImage* canvas, std::list<int> brushSizes);
};

#endif // PAINT_H
