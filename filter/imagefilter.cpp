#include "imagefilter.h"

ImageFilter::ImageFilter(QObject *parent) : QObject{parent} {}

QImage ImageFilter::operator()(const QImage &img, int size, double strength, int pass) const
{
    QImage &&modImg = QImage{img};
    for (int i=0;i<pass;i++) modImg = apply(modImg, size, getNormFactor() * strength);
    return modImg;
}

bool ImageFilter::sizeEnabled() const
{
    return true;
}

bool ImageFilter::strengthEnabled() const
{
    return true;
}
