#ifndef HELPERS_H
#define HELPERS_H

#include <QImage>
#include "smartpointerhelp.h"
#include "stroke.h"
#include "glm/vec3.hpp"
#include "glm/mat3x3.hpp"
#include "math.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <QThreadPool>
#include <iostream>
#include <cmath>

struct JitterParams {
    float hueJitter, satJitter, valueJitter, redJitter, greenJitter, blueJitter;

    JitterParams() :
        hueJitter(0.f), satJitter(0.f), valueJitter(0.f),
        redJitter(0.f), greenJitter(0.f), blueJitter(0.f)
    {}

    JitterParams(float hueJitter, float satJitter, float valueJitter,
                 float redJitter, float greenJitter, float blueJitter) :
        hueJitter(hueJitter), satJitter(satJitter), valueJitter(valueJitter),
        redJitter(redJitter), greenJitter(greenJitter), blueJitter(blueJitter)
    {}
};

// Caps c to [0, 255]
int cap(int c);

// Returns QColor in range [0, 255]
QColor getColor(QImage* image, int x, int y);

bool outOfBounds(int x, int y, QImage* image);

float gradient(int x, int y, QImage* image);

glm::vec3 colorAt(int x, int y, QImage* image);

int jitter(int value, float jitter);

QColor jitterColor(QColor color, JitterParams& jParams);

uPtr<Stroke> paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas, QImage* gradientImage,
                         int maxStrokeLength, int minStrokeLength, float curvatureFilter, JitterParams& jParams);

glm::vec3 areaError(int x, int y, int grid, QImage* reference, QImage* canvas);

uPtr<QImage> resizeBrushImage(QImage* brushRef, float radius, float brushImageSize);

#endif // HELPERS_H
