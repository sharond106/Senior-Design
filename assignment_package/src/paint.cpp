#include "paint.h"
#include "glm/mat3x3.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include "glm/trigonometric.hpp"

bool TESTING = false;

struct byKey {
    bool operator()(uPtr<Stroke> const &a, uPtr<Stroke> const &b) const {
        return a.get()->randomKey < b.get()->randomKey;
    }
};

Paint::Paint()
{}

uPtr<QImage> Paint::sobelFilter(QImage* image) {
    uPtr<QImage> filteredImage = mkU<QImage>(image->width(), image->height(),  QImage::Format_RGB32);
    glm::mat3 horizontal = glm::mat3(0.);
    glm::mat3 vertical = glm::mat3(0.);

    horizontal[0].x = -3.;
    horizontal[0].y = -10.;
    horizontal[0].z = -3.;
    horizontal[2].x = 3.;
    horizontal[2].y = 10.;
    horizontal[2].z = 3.;
    vertical[0].x = 3.;
    vertical[0].y = 0.;
    vertical[0].z = -3.;
    vertical[1].x = 10.;
    vertical[1].y = 0.;
    vertical[1].z = -10.;
    vertical[2].x = 3.;
    vertical[2].y = 0.;
    vertical[2].z = -3.;

    int width = image->width();
    int height = image->height();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            glm::vec3 hSum = glm::vec3(0.);
            glm::vec3 vSum = glm::vec3(0.);

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (x + i < 0 || x + i >= width || y + j < 0 || y + j >= height) {
                        continue;
                    }
                    QColor color = image->pixelColor(x + i, y + j);
                    float luminance = 0.30 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
                    glm::vec3 colorVec = glm::vec3(luminance);
                    hSum += horizontal[i + 1][j + 1] * colorVec;
                    vSum += vertical[i + 1][j + 1] * colorVec;
                }
            }
            glm::vec3 length = glm::sqrt((hSum * hSum) + (vSum * vSum));

            float theta = atan2(hSum.x, vSum.x) * (180.0/3.141592653589793238463);

            // WHAT IS THIS THRESHOLD SUPPOSED TO BE
            if (length.x > 50) {
                // vertical
                if ((theta >= 70. && theta <= 110.) || (theta <= -70. && theta >= -110.)) {
                    filteredImage->setPixelColor(x, y, QColor(255, 0, 0));
                }
                // horizontal
                else if ((theta >= 160.) || (theta <= 20. && theta >= -20.)) {
                    filteredImage->setPixelColor(x, y, QColor(0, 0, 255));
                }
                else {
                    filteredImage->setPixelColor(x, y, QColor(0, 255, 0));
                }
            } else {
                filteredImage->setPixelColor(x, y, QColor(0.));
            }

//            filteredImage->setPixelColor(x, y, QColor(std::min(length.x, 255.f), std::min(length.y, 255.f), std::min(length.z, 255.f)));
        }
    }
    return filteredImage;
}

float Paint::gradient(int x, int y, QImage* image) {
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

uPtr<QImage> Paint::gaussianBlur(QImage* image) {
    int height = image->height();
    int width = image->width();
    uPtr<QImage> result = mkU<QImage>(image->width(), image->height(),  QImage::Format_RGB32);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            glm::vec3 sum = glm::vec3(0.);
            int counter = 0;
            for (int i = -5; i <= 5; i++) {
                for (int j = -5; j <= 5; j++) {
                    //flooring and ceiling color getting to bounds of image
                    int pix_x = std::max(std::min(x + i, width - 1), 0);
                    int pix_y = std::max(std::min(y + j, height - 1), 0);
                    QColor color = image->pixelColor(pix_x, pix_y);
                    glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                    float scaler = kernel[(j + 5) * 11 + (i + 5)];
                    sum += colorVec * scaler;
                    counter++;
                }
            }
            if (!outOfBounds(x, y, image)) {
                result->setPixelColor(x, y, QColor(sum[0], sum[1], sum[2]));
            } else {
                 std::cout << "BAD " << x << " " << y << std::endl;
            }

        }
    }
    return result;
}

bool Paint::outOfBounds(int x, int y, QImage* image) {
    int width = image->width();
    int height = image->height();
    if (x >= width || y >= height || x < 0 || y < 0) {
        return true;
    }
    return false;
}

glm::vec3 Paint::colorAt(int x, int y, QImage* image) {
    int pix_x = std::max(std::min(x, image->width() - 1), 0);
    int pix_y = std::max(std::min(y, image->height() - 1), 0);
    QColor color = image->pixelColor(pix_x, pix_y);
    return glm::vec3(color.red(), color.green(), color.blue());
}

uPtr<Stroke> Paint::paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas) {
    QColor col = reference->pixelColor(x0, y0);

    if (TESTING) {
        col = QColor(255, 0, 0);
    }
    uPtr<Stroke> stroke = mkU<Stroke>(radius, col, std::pair<int, int>(x0, y0));

    int prevX = x0;
    int prevY = y0;
    // DEFAULT MAX STROKE LENGTH SHOULD BE 4 X RADIUS
    for (int i = 0; i < this->maxStrokeLength; i++) {
        float theta = gradient(prevX, prevY, reference);

        // LOOK HERE FOR BUGS IN FUTURE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (theta + M_PI / 2. <= M_PI / 2.) {
            theta = theta + M_PI / 2.;
        } else {
            theta = theta - M_PI / 2.;
        }
        float deltaX = radius * cos(theta);
        float deltaY = radius * sin(theta);
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
    }
    return stroke;
}

glm::vec3 Paint::areaError(int x, int y, int grid, QImage* reference, QImage* canvas) {
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

bool Paint::inCircle(int x, int y, int centerX, int centerY, float r) {
    x -= centerX;
    y -= centerY;
    if (x*x + y*y <= r*r) {
        return true;
    }
    return false;
}

bool Paint::checkShape(int x, int y, int centerX, int centerY, float r) {
    switch(this->brush) {
    case SQUARE:
        return true;
    case CIRCLE:
        return inCircle(x, y, centerX, centerY, r);
    default:
        return true;
    }
}

void Paint::applyPaint(Stroke* stroke, QImage* canvas) {
    for (std::pair<int, int> point : stroke->points) {

        // MAYBE NOT +1?
        for (int x = point.first - stroke->radius + 1; x < point.first + stroke->radius; x += 1) {
            for (int y = point.second - stroke->radius + 1; y < point.second + stroke->radius; y += 1) {
                if (!outOfBounds(x, y, canvas) && checkShape(x, y, point.first, point.second, stroke->radius)) {
                    canvas->setPixelColor(x, y, stroke->color);
                }
            }
        }
    }
}

void Paint::paintLayer(QImage* reference, QImage* canvas, int brushSize) {
    // NEED TO SOMEHOW CHANGE GAUSSIAN KERNAL BASED ON RADIUS SIZE
    uPtr<QImage> blurredRef = gaussianBlur(reference);
    std::vector<uPtr<Stroke>> zbuf;
    float grid = brushSize;
    for (int x = 0; x < reference->width(); x += grid) {
        for (int y = 0; y < reference->height(); y += grid) {

            // TRY SIMILAR FIX FOR BRIGHT EDGES ON BLURRED IMAGE
            glm::vec3 error = areaError(x, y, grid, blurredRef.get(), canvas);
            if (error[2] > this->errorThreshold) {
                uPtr<Stroke> stroke = paintStroke(error[0], error[1], grid, blurredRef.get(), canvas);
                //std::cout << brushSize << " " << stroke.get()->randomKey << std::endl;
                zbuf.push_back(std::move(stroke));
            }
        }
    }

    //Randomly sort strokes

    std::sort(zbuf.begin(), zbuf.end(), byKey());

    for (int i = 0; i < (int)zbuf.size(); i++) {
        applyPaint(zbuf[i].get(), canvas);
    }
}

void Paint::paint(QImage* reference, QImage* canvas, std::list<int> brushSizes) {
    for (int brushSize : brushSizes) {
        paintLayer(reference, canvas, brushSize);
    }
}

