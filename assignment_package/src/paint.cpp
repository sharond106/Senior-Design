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

float Paint::gaussEquation(float x, float y, float stdev) {
    float exponent = -(x * x + y * y) / (2 * stdev * stdev);
    return exp(exponent) / (2 * M_PI * stdev * stdev);
}

std::vector<float> Paint::generateKernel(int span, float stdev) {
    std::vector<float> blurnel;
    int half = span / 2;
    float sum = 0.f;
    //std::cout << "SIZE " << span << std::endl;
    for (int j = 0; j < span; j++) {
        for (int i = 0; i < span; i++) {         
            float x = i - half;
            float y = j - half;
            //std::cout << " ("<< x << " " << y << " ) ";
            float val = gaussEquation(x, y, stdev);
            blurnel.push_back(val);
            sum += val;         
        }
        //std::cout << " " << std::endl;
    }

    for (int i = 0; i < (int)blurnel.size(); i++) {
        blurnel[i] /= sum;
    }
    return blurnel;
}

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
            QColor color = getColor(image, pix_x,pix_y);
            float luminance = 0.30 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
            glm::vec3 colorVec = glm::vec3(luminance);
            gxSum += gx[i + 1][j + 1] * colorVec;
            gySum += gy[i + 1][j + 1] * colorVec;
        }
    }
    float theta = atan2(gxSum.x, gySum.x);
    return theta;
}

//size is brush size, radius
uPtr<QImage> Paint::gaussianBlur(QImage* image, int size) {
    int height = image->height();
    int width = image->width();
    int kernelLim = size - 1;
    int span = kernelLim * 2 + 1;
    std::vector<float> kernel = generateKernel(span, 1.f);
    uPtr<QImage> result = mkU<QImage>(image->width(), image->height(),  QImage::Format_RGB32);
    if (useThreads) {
        QMutex mutex;
        for (int i = 0; i < threadCount; i++) {
            BlurWorker* w = new BlurWorker(&mutex, i, image, threadCount, kernelLim, span, kernel, result.get());
            QThreadPool::globalInstance()->start(w);
        }
        QThreadPool::globalInstance()->waitForDone();
    } else {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                glm::vec3 sum = glm::vec3(0.);
                int counter = 0;
                for (int i = -kernelLim; i <= kernelLim; i++) {
                    for (int j = -kernelLim; j <= kernelLim; j++) {
                        //flooring and ceiling color getting to bounds of image
                        int pix_x = std::max(std::min(x + i, width - 1), 0);
                        int pix_y = std::max(std::min(y + j, height - 1), 0);
                        QColor color = getColor(image, pix_x, pix_y);
                        glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                        float scaler = kernel[(j + kernelLim) * span + (i + kernelLim)];
                        sum += colorVec * scaler;
                        counter++;
                    }
                }
                if (!BlurWorker::outOfBounds(x, y, image)) {
                    result->setPixelColor(x, y, QColor(cap(sum[0]), cap(sum[1]), cap(sum[2])));
                } else {
                     std::cout << "BAD " << x << " " << y << std::endl;
                }

            }
        }
    }
    return result;
}

int Paint::cap(int c) {
    return std::max(std::min(c, 255), 0);
}

QColor Paint::getColor(QImage* image, int x, int y) {
    QColor color = image->pixelColor(x, y);
    color.setRed(cap(color.red()));
    color.setGreen(cap(color.green()));
    color.setBlue(cap(color.blue()));
    return color;
}

glm::vec3 Paint::colorAt(int x, int y, QImage* image) {
    int pix_x = std::max(std::min(x, image->width() - 1), 0);
    int pix_y = std::max(std::min(y, image->height() - 1), 0);
    QColor color = getColor(image, pix_x, pix_y);
    return glm::vec3(color.red(), color.green(), color.blue());
}

uPtr<Stroke> Paint::paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas) {
    QColor col = getColor(reference, x0, y0);

    if (TESTING) {
        col = QColor(255, 0, 0);
    }
    uPtr<Stroke> stroke = mkU<Stroke>(radius, col, std::pair<int, int>(x0, y0));

    int prevX = x0;
    int prevY = y0;
    float prevDeltaX = 0.;
    float prevDeltaY = 0.;

    // default max length = 4 X radius
    if (this->maxStrokeLength == -1) {
        this->maxStrokeLength = 4 * radius;
    }
    for (int i = 0; i < this->maxStrokeLength; i++) {
        float theta = 0.f;
        if (this->brushImage != nullptr) {
            theta = gradient(prevX, prevY, this->brushImage.get());
        } else {
            theta = gradient(prevX, prevY, reference);
        }

        if (theta + M_PI / 2. <= M_PI / 2.) {
            theta = theta + M_PI / 2.;
        } else {
            theta = theta - M_PI / 2.;
        }

        float deltaX = radius * cos(theta);
        float deltaY = radius * sin(theta);

        // Curvature filter
        deltaX = (this->curvatureFilter * deltaX) + ((1. - this->curvatureFilter) * prevDeltaX);
        deltaY = (this->curvatureFilter * deltaY) + ((1. - this->curvatureFilter) * prevDeltaY);

        int x = prevX + round(deltaX);
        int y = prevY + round(deltaY);
        if (BlurWorker::outOfBounds(x, y, reference)) {
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

float Paint::jitter(int value, float jitter) {
    if (jitter <= 0.) {
        return value;
    }
    // HOW DO I JITTER THIS

}

QColor Paint::jitterColor(QColor color) {
    float hue = jitter(color.hue(), this->hueJitter);
    float saturation = jitter(color.saturation(), this->satJitter);

    // DO THE REST OF THE JITTERS AND THEN RETURN THE NEW COLOR

}

void Paint::applyPaint(Stroke* stroke, QImage* canvas) {
    for (std::pair<int, int> point : stroke->points) {

        // MAYBE NOT +1?
        for (int x = point.first - stroke->radius + 1; x < point.first + stroke->radius; x += 1) {
            for (int y = point.second - stroke->radius + 1; y < point.second + stroke->radius; y += 1) {
                if (!BlurWorker::outOfBounds(x, y, canvas) && checkShape(x, y, point.first, point.second, stroke->radius)) {
                    canvas->setPixelColor(x, y, QColor(stroke->color.red(), stroke->color.green(), stroke->color.blue()));
                }
            }
        }
    }
}

void Paint::paintLayer(QImage* reference, QImage* canvas, int brushSize) {
    uPtr<QImage> blurredRef = gaussianBlur(reference, brushSize);

    // if using separate image for brush stroke direction
    if (this->brushImage != nullptr) {
        this->brushImage = gaussianBlur(this->brushImage.get(), brushSize);
    }

    std::vector<uPtr<Stroke>> zbuf;
    float grid = brushSize;
    for (int x = 0; x < reference->width(); x += grid) {
        for (int y = 0; y < reference->height(); y += grid) {

            // TRY SIMILAR FIX FOR BRIGHT EDGES ON BLURRED IMAGE
            glm::vec3 error = areaError(x, y, grid, blurredRef.get(), canvas);
            if (error[2] > this->errorThreshold) {
                uPtr<Stroke> stroke = paintStroke(error[0], error[1], grid, blurredRef.get(), canvas);
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

