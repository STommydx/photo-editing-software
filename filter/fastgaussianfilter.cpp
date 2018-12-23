/**
 * @class FastGaussianFilter
 * @brief The FastGaussianFilter class provides an efficent implementation of gaussian blur filter.
 *
 * This filter is implemented using kernel convolution of GaussianKernel.
 * It provides a nice looking edge-preserve bluring effect and is widely used in image processing.
 *
 * Unlike GaussianBlueFilter, the filter is implemented using two convolutions of 1D gaussian kernel.
 *
 * @sa GaussianKernel, GaussianBlurFilter
 */

#include "fastgaussianfilter.h"
#include "gaussiankernel.h"

/**
 * @brief Constuct a gaussian blur filter with the given @a parent
 * @param parent the parent QObject
 */
FastGaussianFilter::FastGaussianFilter(QObject *parent) : ImageFilter{parent} {}

QImage FastGaussianFilter::apply(const QImage &img, int size, double strength) const
{
    GaussianKernel xKernel{size, 1, strength};
    GaussianKernel yKernel{1, size, strength};
    connect(&xKernel, &ImageKernel::progressUpdated, [&](int progress) {
        if (~progress & 1) emit progressUpdated(progress / 2);
    });
    connect(&yKernel, &ImageKernel::progressUpdated, [&](int progress) {
        if (~progress & 1) emit progressUpdated(img.height() / 2 + progress / 2);
    });
    return yKernel.convolution(xKernel.convolution(img));
}

QString FastGaussianFilter::getName() const
{
    return "Gaussian Blur (Large Size)";
}

int FastGaussianFilter::getMaxSize() const
{
    return 200;
}

double FastGaussianFilter::getNormFactor() const
{
    return 5.0;
}
