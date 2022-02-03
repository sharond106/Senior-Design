#include "paint.h"
#include "glm/mat3x3.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <algorithm>

Paint::Paint()
{}

uPtr<QImage> Paint::sobelFilter(QImage* image) {
    uPtr<QImage> filteredImage = mkU<QImage>(image->width(), image->height(),  QImage::Format_RGB32);
    glm::mat3 horizontal = glm::mat3(0.);
    glm::mat3 vertical = glm::mat3(0.);

    horizontal[0].x = 3.;
    horizontal[0].y = 10.;
    horizontal[0].z = 3.;
    horizontal[2].x = -3.;
    horizontal[2].y = -10.;
    horizontal[2].z = -3.;
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
                    glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                    hSum += horizontal[i + 1][j + 1] * colorVec;
                    vSum += vertical[i + 1][j + 1] * colorVec;
                }
            }
            glm::vec3 length = glm::sqrt((hSum * hSum) + (vSum * vSum));
//            std::cout << length.x << " " << length.y << " " << length.z << std::endl;
            filteredImage->setPixelColor(x, y, QColor(std::min(length.x, 255.f), std::min(length.y, 255.f), std::min(length.z, 255.f)));
        }
    }
    return filteredImage;
}

QImage Paint::GaussianBlur(QImage image) {

    int height = image.height();
    int width = image.width();
    QImage result(width, height, QImage::Format_RGB32);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            glm::vec3 sum = glm::vec3(0.);
            int counter = 0;
            for (int i = -5; i <= 5; i++) {
                for (int j = -5; j <= 5; j++) {
                    if (x + i >= width || x + i < 0 || y + j >= height || y + j < 0) {
                        continue;
                    } else {
                        QColor color = image.pixelColor(x + i, y + j);
                        glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                        float scaler = kernel[(j + 5) * 11 + (i + 5)];
                        sum += colorVec * scaler;
                        counter++;
                    }
                }
            }
            result.setPixelColor(x, y, QColor(sum[0], sum[1], sum[2]));
        }
    }
    return image;
}
