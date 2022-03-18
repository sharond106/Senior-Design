#include "paint.h"



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
                        QColor color = image->pixelColor(pix_x, pix_y);
                        glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                        float scaler = kernel[(j + kernelLim) * span + (i + kernelLim)];
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
    }
    return result;
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
                    QColor colorWithOpacity = QColor(stroke->color.red(), stroke->color.green(), stroke->color.blue(), this->opacity);
                    canvas->setPixelColor(x, y, colorWithOpacity);
//                    canvas->setPixelColor(x, y, stroke->color);
                }
            }
        }
    }
}

void Paint::paintLayer(QImage* reference, QImage* canvas, int brushSize) {
    // NEED TO SOMEHOW CHANGE GAUSSIAN KERNAL BASED ON RADIUS SIZE
    uPtr<QImage> blurredRef = gaussianBlur(reference, brushSize);
    // if using separate image for brush stroke direction
    // DO I NEED TO MAKE THIS A UNIQUE PTR????????????????????????
    if (this->brushImage != nullptr) {
        this->brushImage = gaussianBlur(this->brushImage.get(), brushSize);
    }

    std::vector<uPtr<Stroke>> zbuf;
    float grid = brushSize;
    if (useThreads) {
    //if (false) {
        QMutex mutex;
        for (int x = 0; x < reference->width(); x += grid) {
            for (int y = 0; y < reference->height(); y += grid) {
                StrokeWorker* w = new StrokeWorker(x, y, grid, &mutex, blurredRef.get(), canvas, this->brushImage.get(),
                                                   this->maxStrokeLength, this->minStrokeLength, this->curvatureFilter, &zbuf);
                QThreadPool::globalInstance()->start(w);
            }
        }
        QThreadPool::globalInstance()->waitForDone();
    } else {
        for (int x = 0; x < reference->width(); x += grid) {
            for (int y = 0; y < reference->height(); y += grid) {

                // TRY SIMILAR FIX FOR BRIGHT EDGES ON BLURRED IMAGE
                glm::vec3 error = areaError(x, y, grid, blurredRef.get(), canvas);
                if (error[2] > this->errorThreshold) {
                    uPtr<Stroke> stroke = paintStroke(error[0], error[1], grid, blurredRef.get(), canvas, this->brushImage.get(),
                            this->maxStrokeLength, this->minStrokeLength, this->curvatureFilter);
                    //std::cout << brushSize << " " << stroke.get()->randomKey << std::endl;
                    zbuf.push_back(std::move(stroke));
                }
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

