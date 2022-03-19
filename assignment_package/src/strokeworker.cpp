#include "strokeworker.h"

StrokeWorker::StrokeWorker() {}

StrokeWorker::StrokeWorker(int x, int y, int grid, QMutex* mutex, QImage* reference, QImage* blurred, QImage* brushImage,
                           int maxStrokeLength, int minStrokeLength, float curvatureFilter, std::vector<uPtr<Stroke>>* zbuf, JitterParams& jParams) :
    maxStrokeLength(maxStrokeLength), minStrokeLength(minStrokeLength), curvatureFilter(curvatureFilter), x(x), y(y), grid(grid),
    mutex(mutex), reference(reference), blurred(blurred), brushImage(brushImage), zbuf(zbuf), jParams(jParams)

{}

void StrokeWorker::run() {
    glm::vec3 error = areaError(x, y, grid, reference, blurred);
    if (error[2] > this->errorThreshold) {
        uPtr<Stroke> stroke = paintStroke(error[0], error[1], grid, reference, blurred, brushImage,
                this->maxStrokeLength, this->minStrokeLength, this->curvatureFilter, this->jParams);
        //std::cout << brushSize << " " << stroke.get()->randomKey << std::endl;
        mutex->lock();
        zbuf->push_back(std::move(stroke));
        mutex->unlock();
    }
}



