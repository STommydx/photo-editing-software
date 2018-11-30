#include "imagesizefilter.h"

QImage ImageSizeFilter::apply(const QImage &img, int size, double) const
{
    return apply(img, size);
}

double ImageSizeFilter::getNormFactor() const
{
    return 1.0;
}

bool ImageSizeFilter::strengthEnabled() const
{
    return false;
}
