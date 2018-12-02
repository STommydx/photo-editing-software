/**
 * @class EmbossFilter
 * @brief The EmbossFilter class represents an emboss filter.
 *
 * This filter is implemented using kernel convolution of EmbossKernel.
 * It is used to enhance the amptitude of high frequency image signals at edges.
 *
 * @sa EmbossKernel
 */

#include "embossfilter.h"
#include "embosskernel.h"

/**
 * @brief Constructs an emboss filter with the given @a parent
 * @param parent the parent @c QObject
 */
EmbossFilter::EmbossFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString EmbossFilter::getName() const
{
    return "Emboss";
}

int EmbossFilter::getMaxSize() const
{
    return 5;
}

QImage EmbossFilter::apply(const QImage &img, int size) const
{
    EmbossKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
