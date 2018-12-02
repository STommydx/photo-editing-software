/**
 * @class GaussianBlurFilter
 * @brief The GaussianBlurFilter class represents a gaussian blur filter.
 *
 * This filter is implemented using kernel convolution of GaussianKernel.
 * It provides a nice looking edge-preserve bluring effect and is widely used in image processing.
 *
 * @sa GaussianKernel
 */

#include "gaussianblurfilter.h"
#include "gaussiankernel.h"

/**
 * @brief Constuct a gaussian blur filter with the given @a parent
 * @param parent the parent QObject
 */
GaussianBlurFilter::GaussianBlurFilter(QObject *parent) : ImageFilter{parent} {}

QImage GaussianBlurFilter::apply(const QImage &img, int size, double strength) const
{
    GaussianKernel kernel{size, strength};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}

QString GaussianBlurFilter::getName() const
{
    return "Gaussian Blur";
}

int GaussianBlurFilter::getMaxSize() const
{
    return 10;
}

double GaussianBlurFilter::getNormFactor() const
{
    return 5.0;
}
