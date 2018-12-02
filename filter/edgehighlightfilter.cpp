/**
 * @class EdgeHighlightFilter
 * @brief The EdgeHighlightFilter class represents an edge highlight filter.
 *
 * This filter is implemented using kernel convolution of EdgeDetectKernel.
 * It highlights high frequency gradient change of the image.
 *
 * @sa EdgeDetectKernel
 */

#include "edgehighlightfilter.h"
#include "edgedetectkernel.h"

/**
 * @brief Constructs an edge highlight filter with the given @a parent
 * @param parent the parent @c QObject
 */
EdgeHighlightFilter::EdgeHighlightFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString EdgeHighlightFilter::getName() const
{
    return "Edge Highlight";
}

int EdgeHighlightFilter::getMaxSize() const
{
    return 5;
}

QImage EdgeHighlightFilter::apply(const QImage &img, int size) const
{
    EdgeDetectKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}

