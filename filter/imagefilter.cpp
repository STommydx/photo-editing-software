#include "imagefilter.h"

QImage ImageFilter::operator()(const QImage &img, int size, double strength) const
{
    return apply(img, size, getNormFactor() * strength);
}

bool ImageFilter::sizeEnabled() const
{
    return true;
}

bool ImageFilter::strengthEnabled() const
{
    return true;
}
