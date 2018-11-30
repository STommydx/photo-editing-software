#include "edgehighlightfilter.h"
#include "imagekernel.h"

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
    return ImageKernel::edgeDetect(size).convolution(img);
}
