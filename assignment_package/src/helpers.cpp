#pragma once

#include "helpers.h"
//Returns true if the coordinates defined by x and y is out of bounds for the image

int cap(int c) {
    return std::max(std::min(c, 255), 0);
}

QColor getColor(QImage* image, int x, int y) {
    int pix_x = std::max(std::min(x, image->width() - 1), 0);
    int pix_y = std::max(std::min(y, image->height() - 1), 0);
    QColor color = image->pixelColor(pix_x, pix_y);
    color.setRed(cap(color.red()));
    color.setGreen(cap(color.green()));
    color.setBlue(cap(color.blue()));
    return color;
}

bool outOfBounds(int x, int y, QImage* image) {
    int width = image->width();
    int height = image->height();
    if (x >= width || y >= height || x < 0 || y < 0) {
        return true;
    }
    return false;
}

// Returns gradient orientation of sobel filtered image at x, y
// [-pi, pi]
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
            QColor color = getColor(image, pix_x, pix_y);
            float luminance = 0.30 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
            glm::vec3 colorVec = glm::vec3(luminance);
            gxSum += gx[i + 1][j + 1] * colorVec;
            gySum += gy[i + 1][j + 1] * colorVec;
        }
    }
    float theta = atan2(gxSum.x, gySum.x);
    return theta;
}

// Returns RGB [0-255]
glm::vec3 colorAt(int x, int y, QImage* image) {
    QColor color = getColor(image, x, y);
    return glm::vec3(color.red(), color.green(), color.blue());
}

int jitter(int value, float jitter) {
    if (jitter <= 0.) {
        return value;
    }
    // Change this value to reduce the randomness of the jittering
    float range = jitter * 100;
    int max = std::min(value + range/2., 255.);
    int min = std::max(value - range/2., 0.);
    if (min > max) {
        min = max - 1;
    }
    return rand()%(max-min + 1) + min;
}

QColor jitterColor(QColor color, JitterParams& jParams) {
    color = color.toHsv();

    //int hue = jitter(color.hue(), jParams.hueJitter);
    int hue = color.hue();
    if (jParams.hueJitter > 0.) {
        // Change this value to reduce the randomness of the jittering
        float range = jParams.hueJitter * 100;
        int max = color.hue() + range/2.;
        int min = color.hue() - range/2.;
        // make range positive by shifting up
        if (min < 0) {
            max -= min;
            min = 0;
        }
        // this is giving HSV parameters out of range
        hue = (rand()%(max-min + 1) + min) % 360;
    }

    int saturation = jitter(color.saturation(), jParams.satJitter);
    int value = jitter(color.value(), jParams.valueJitter);

    color.setHsv(hue, saturation, value);

    int red = jitter(color.red(), jParams.redJitter);
    int green = jitter(color.green(), jParams.greenJitter);
    int blue = jitter(color.blue(), jParams.blueJitter);
    QColor newColor = QColor(cap(red), cap(green), cap(blue));

    return newColor;
}

uPtr<Stroke> paintStroke(int x0, int y0, int radius, QImage* reference, QImage* canvas, QImage* gradientImage,
                         int maxStrokeLength, int minStrokeLength, float curvatureFilter, JitterParams& jParams) {
    QColor col = getColor(reference, x0, y0);

    col = jitterColor(col, jParams);
    uPtr<Stroke> stroke = mkU<Stroke>(radius, col, std::pair<int, int>(x0, y0));

    int prevX = x0;
    int prevY = y0;
    float prevDeltaX = 0.;
    float prevDeltaY = 0.;
    // DEFAULT MAX STROKE LENGTH SHOULD BE 4 X RADIUS (not doing this also won't allow the second image for gradient to work)
    if (maxStrokeLength < 0) {
        maxStrokeLength = 4 * radius;
    }
    //Hacky adjustment here, need to calculate angle at each point
    //So do that calculation then break from the loop
    for (int i = 0; i < maxStrokeLength + 1; i++) {
        float theta = 0.f;
        if (gradientImage != nullptr) {
            theta = gradient(prevX, prevY, gradientImage);
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

        //Compute unit vector and plug into atan2. yields angle in radians
        float length = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        stroke->addAngle(std::atan2(deltaY / length, deltaX / length));
        if (i < maxStrokeLength) {
            return stroke;
        }
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

// Returns x, y of largest error and the error of the area
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

uPtr<QImage> resizeBrushImage(QImage* brushRef, float radius, float brushImageSize) {
    float length = std::sqrt(std::pow(brushRef->width(), 2) + std::pow(brushRef->height(), 2));
    float scale = radius / length * std::pow(2.f, brushImageSize / 10.);
    uPtr<QImage>brushImage = mkU<QImage>(*brushRef);
    *brushImage = brushImage->scaled(brushRef->width() * scale, brushRef->height() * scale, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    //We grey scale the image and flip
    for (int i = 0; i < brushImage->width(); i++) {
        for (int j = 0; j < brushImage->height(); j++) {
             QColor color = brushImage->pixelColor(i, j);
             float luminance = 0.30 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
             if (luminance < 250) {
                 int z = 1;
             }
             brushImage->setPixelColor(i, j, QColor(255 - luminance, 255 - luminance, 255 - luminance));
        }
    }
    return brushImage;
}
