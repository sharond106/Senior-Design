#include "strokeworker.h"

StrokeWorker::StrokeWorker() {}

StrokeWorker::StrokeWorker(int x, int y, int grid, QMutex* mutex, QImage* reference,
                           QImage* blurred, std::vector<uPtr<Stroke>>* zbuf) :
    x(x), y(y), grid(grid), mutex(mutex), reference(reference), blurred(blurred), zbuf(zbuf)

{}

void StrokeWorker::run() {

}



