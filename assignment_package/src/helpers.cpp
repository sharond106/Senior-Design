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

bool outOfBounds(int x, int y, QImage* image) {
    int width = image->width();
    int height = image->height();
    if (x >= width || y >= height || x < 0 || y < 0) {
        return true;
    }
    return false;
}

float gradient(int x, int y, QImage* image) {
    glm::mat3 gx = glm::mat3(0.);
    glm::mat3 gy = glm::mat3(0.);

    gx[0].x = 3.;
    gx[0].z = -3.;
    gx[1].x = 10.;
    gx[1].z = -10.;
    gx[2].x = 3.;
    gx[2].z = -3.;
    gy[0].x = 3.;
    gy[0].y = 10.;
    gy[0].z = 3.;
    gy[2].x = -3.;
    gy[2].y = -10.;
    gy[2].z = -3.;

    int width = image->width();
    int height = image->height();

    glm::vec3 gySum = glm::vec3(0.);
    glm::vec3 gxSum = glm::vec3(0.);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int pix_x = std::max(std::min(x + i, width - 1), 0);
            int pix_y = std::max(std::min(y + j, height - 1), 0);
            QColor color = image->pixelColor(pix_x,pix_y);
            float luminance = 0.30 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
            glm::vec3 colorVec = glm::vec3(luminance);
            gxSum += gx[i + 1][j + 1] * colorVec;
            gySum += gy[i + 1][j + 1] * colorVec;
        }
    }
    float theta = atan2(gxSum.x, gySum.x);
    return theta;
}

glm::vec3 colorAt(int x, int y, QImage* image) {
    int pix_x = std::max(std::min(x, image->width() - 1), 0);
    int pix_y = std::max(std::min(y, image->height() - 1), 0);
    QColor color = image->pixelColor(pix_x, pix_y);
    return glm::vec3(color.red(), color.green(), color.blue());
}

uPtr<Stroke> paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas, QImage* brushImage,
                         int maxStrokeLength, int minStrokeLength, float curvatureFilter) {
    QColor col = reference->pixelColor(x0, y0);

    uPtr<Stroke> stroke = mkU<Stroke>(radius, col, std::pair<int, int>(x0, y0));

    int prevX = x0;
    int prevY = y0;
    float prevDeltaX = 0.;
    float prevDeltaY = 0.;
    // DEFAULT MAX STROKE LENGTH SHOULD BE 4 X RADIUS
    for (int i = 0; i < maxStrokeLength; i++) {
        float theta = 0.f;
        if (brushImage != nullptr) {
            theta = gradient(prevX, prevY, brushImage);
        } else {
            theta = gradient(prevX, prevY, reference);
        }


        // LOOK HERE FOR BUGS IN FUTURE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (theta + M_PI / 2. <= M_PI / 2.) {
            theta = theta + M_PI / 2.;
        } else {
            theta = theta - M_PI / 2.;
        }

        float deltaX = radius * cos(theta);
        float deltaY = radius * sin(theta);

        // Curvature filter
        deltaX = (curvatureFilter * deltaX) + ((1. - curvatureFilter) * prevDeltaX);
        deltaY = (curvatureFilter * deltaY) + ((1. - curvatureFilter) * prevDeltaY);

        int x = prevX + round(deltaX);
        int y = prevY + round(deltaY);
        if (outOfBounds(x, y, reference)) {
            return stroke;
        }
        if (i > minStrokeLength && glm::distance(colorAt(x, y, reference), colorAt(x, y, canvas)) <
                                   glm::distance(colorAt(x, y, reference), colorAt(x0, y0, reference))) {
            return stroke;
        }
        stroke->addPoint(x, y);
        prevX = x;
        prevY = y;
        prevDeltaX = deltaX;
        prevDeltaY = deltaY;
    }
    return stroke;
}

glm::vec3 areaError(int x, int y, int grid, QImage* reference, QImage* canvas) {
    float error = 0.f;
    float max = 0.f;
    int maxX;
    int maxY;
    for (int i = std::max(x - grid / 2., 0.); i < std::min(double(reference->width()), x + grid / 2.); i += 1) {
        for (int j = std::max(y - grid / 2., 0.); j < std::min(double(reference->height()), y + grid / 2.); j += 1) {
            float currError = glm::distance(colorAt(i, j, reference), colorAt(i, j, canvas));
            if (currError > max) {
                max = currError;
                maxX = i;
                maxY = j;
            }
            error += currError;
        }
    }
    return glm::vec3(maxX, maxY, error);
}
