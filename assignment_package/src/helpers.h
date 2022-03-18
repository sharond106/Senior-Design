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

bool outOfBounds(int x, int y, QImage* image);

float gradient(int x, int y, QImage* image);

glm::vec3 colorAt(int x, int y, QImage* image);

uPtr<Stroke> paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas, QImage* brushImage,
                         int maxStrokeLength, int minStrokeLength, float curvatureFilter);

glm::vec3 areaError(int x, int y, int grid, QImage* reference, QImage* canvas);

#endif // HELPERS_H
