/**
 * @class MeanBlurFilter
 * @brief The MeanBlurFilter class represents a mean blur filter.
 *
 * This filter is implemented using kernel convolution of MeanKernel.
 * It provides a edge-preserve blurring effect and is widely used in image processing.
 *
 * @sa MeanKernel
 */

#include "meanblurfilter.h"
#include "meankernel.h"

/**
 * @brief Constuct a mean blur filter with the given @a parent
 * @param parent the parent QObject
 */
MeanBlurFilter::MeanBlurFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString MeanBlurFilter::getName() const
{
    return "Mean Blur";
}

int MeanBlurFilter::getMaxSize() const
{
    return 10;
}

QImage MeanBlurFilter::apply(const QImage &img, int size) const
{
    MeanKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
