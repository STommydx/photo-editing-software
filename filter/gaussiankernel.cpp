/**
 * @class GaussianKernel
 * @brief The GaussianKernel class represents the a normal distributed kernel for gaussian blur filter.
 * @sa GaussianBlurFilter
 */

#include "gaussiankernel.h"

#include <QtMath>

/**
 * @brief Construct an edge detect kernel with a x-radius of @a sizeX and a y-radius of @a sizeY.
 *
 * An gaussian kernel with a dimension ( @a sizeX * @c 2 - @c 1) * ( @a sizeY * @c 2 - @c 1) is constructed.
 * The weight is generated using a gaussian distribution with the mean being the center pixel.
 *
 * @param sizeX radius of the kernel x-dimension
 * @param sizeY radius of the kernel y-dimension
 * @param sd the standard deviation of the gaussian distrubution
 * @param parent the parent @c QObject
 */
GaussianKernel::GaussianKernel(int sizeX, int sizeY, double sd, QObject *parent) : ImageKernel{sizeX, sizeY, parent}
{
    const int MULTIPLIER = 1000;
    for (int dx=-sizeX+1;dx<sizeX;dx++) for (int dy=-sizeY+1;dy<sizeY;dy++) {
        int sqDist = dx * dx + dy * dy; // calculate squared distance to plug in the distribution formula
        double density = 1.0 / qSqrt(2.0 * M_PI * sd * sd) * qExp(-sqDist / 2.0 / sd / sd); // calculate density using gaussian distribution formula
        data(dx, dy) = qFloor(density * MULTIPLIER); // multiply by a large constant to increase precision
    }
}

/**
 * @brief Construct an edge detect kernel with a radius of @a size.
 *
 * An gaussian kernel with a dimension ( @a size * @c 2 - @c 1) * ( @a size * @c 2 - @c 1) is constructed.
 * The weight is generated using a gaussian distribution with the mean being the center pixel.
 *
 * @param size radius of the kernel
 * @param sd the standard deviation of the gaussian distrubution
 * @param parent the parent @c QObject
 */
GaussianKernel::GaussianKernel(int size, double sd, QObject *parent) : GaussianKernel{size, size, sd, parent} {}
