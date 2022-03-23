#ifndef BLURWORKER_H
#define BLURWORKER_H
#include <QRunnable>
#include <QString>
#include <QMutex>
#include <QImage>
#include "glm/mat3x3.hpp"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include "glm/trigonometric.hpp"
#include "helpers.h"

class BlurWorker : public QRunnable
{
public:
    int id;
    int kernelLim;
    int span;
    int threadCount;
    std::vector<float> kernel;
    QMutex* mutex;
    QImage* reference;
    QImage* blurred;


    BlurWorker();
    BlurWorker(QMutex* mutex, int id, QImage* reference, int threadCount,
               int kernelLim, int span, std::vector<float>& kernel, QImage* blurred);
    void run() override;
};

#endif // BLURWORKER_H
