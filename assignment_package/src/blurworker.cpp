#include "blurworker.h"

BlurWorker::BlurWorker() {}

BlurWorker::BlurWorker(QMutex* mutex, int id, QImage* reference, int threadCount,
                       int kernelLim, int span, std::vector<float>& kernel, QImage* blurred) :
    id(id), kernelLim(kernelLim), span(span), threadCount(threadCount), kernel(kernel), mutex(mutex), reference(reference), blurred(blurred)
{}

void BlurWorker::run() {
    int height = reference->height();
    int width = reference->width();
    //counter set to id
    int tracker = id;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (tracker != 0) {
                //This skips work handled by other threads
                //std::cout << "skip" << std::endl;
                tracker--;
            } else {
                //Once work is done reset counter again.
                tracker = threadCount - 1;
                if (id == 0) {
                    //std::cout << counter << std::endl;
                    //std::cout << "(" << x << ", " << y << ")" << std::endl;
                }
                glm::vec3 sum = glm::vec3(0.);
                int counter = 0;
                for (int i = -kernelLim; i <= kernelLim; i++) {
                    for (int j = -kernelLim; j <= kernelLim; j++) {
                        //flooring and ceiling color getting to bounds of image
                        int pix_x = std::max(std::min(x + i, width - 1), 0);
                        int pix_y = std::max(std::min(y + j, height - 1), 0);
                        QColor color = reference->pixelColor(pix_x, pix_y);
                        glm::vec3 colorVec = glm::vec3(color.red(), color.green(), color.blue());
                        float scaler = kernel[(j + kernelLim) * span + (i + kernelLim)];
                        sum += colorVec * scaler;
                        counter++;
                    }
                }
                if (!outOfBounds(x, y, reference)) {
                    mutex->lock();
                    blurred->setPixelColor(x, y, QColor(sum[0], sum[1], sum[2]));
                    mutex->unlock();
                } else {
                     std::cout << "BAD " << x << " " << y << std::endl;
                }

            }
        }
    }
}

bool BlurWorker::outOfBounds(int x, int y, QImage* image) {
    int width = image->width();
    int height = image->height();
    if (x >= width || y >= height || x < 0 || y < 0) {
        return true;
    }
    return false;
}
