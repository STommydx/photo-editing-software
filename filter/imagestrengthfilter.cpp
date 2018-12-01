#include "imagestrengthfilter.h"

ImageStrengthFilter::ImageStrengthFilter(QObject *parent) : ImageFilter{parent} {}

QImage ImageStrengthFilter::apply(const QImage &img, int, double strength) const
{
    return apply(img, strength);
}

int ImageStrengthFilter::getMaxSize() const
{
    return 10;
}

bool ImageStrengthFilter::sizeEnabled() const
{
    return false;
}