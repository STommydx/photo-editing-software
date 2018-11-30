#include "edgehighlightfilter.h"
#include "imagekernel.h"

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
