#include "edgehighlightfilter.h"
#include "edgedetectkernel.h"

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

