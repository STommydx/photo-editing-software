#include "imagepurefilter.h"

ImagePureFilter::ImagePureFilter(QObject *parent) : ImageSizeFilter{parent} {}

int ImagePureFilter::getMaxSize() const
{
    return 10;
}

bool ImagePureFilter::sizeEnabled() const
{
    return false;
}

QImage ImagePureFilter::apply(const QImage &img, int size, double strength) const
{
    return ImageSizeFilter::apply(img, size, strength);
}

QImage ImagePureFilter::apply(const QImage &img, int) const
{
    return apply(img);
}
