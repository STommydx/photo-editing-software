/**
 * @class SharpenFilter
 * @brief The SharpenFilter class represents an sharpen filter.
 *
 * This filter is implemented using kernel convolution of SharpenKernel.
 * It is used to enhance the amptitude of high frequency image signals at edges.
 *
 * @sa SharpenKernel
 */

#include "sharpenfilter.h"
#include "sharpenkernel.h"

/**
 * @brief Constructs a sharpen filter with the given @a parent
 * @param parent the parent @c QObject
 */
SharpenFilter::SharpenFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString SharpenFilter::getName() const
{
    return "Sharpen";
}

int SharpenFilter::getMaxSize() const
{
    return 5;
}

QImage SharpenFilter::apply(const QImage &img, int size) const
{
    SharpenKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
