#include "gaussiankernel.h"

#include <QtMath>

GaussianKernel::GaussianKernel(int size, double sd, QObject *parent) : ImageKernel{size, parent}
{
    const int MULTIPLIER = 1000;
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        int sqDist = dx * dx + dy * dy;
        double density = 1.0 / qSqrt(2.0 * M_PI * sd * sd) * qExp(-sqDist / 2.0 / sd / sd);
        data(dx, dy) = qFloor(density * MULTIPLIER);
    }
}
