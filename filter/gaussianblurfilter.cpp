#include "gaussianblurfilter.h"
#include "imagekernel.h"

GaussianBlurFilter::GaussianBlurFilter(QObject *parent) : ImageFilter{parent} {}

QImage GaussianBlurFilter::apply(const QImage &img, int size, double strength) const
{
    return ImageKernel::gaussianBlur(size, strength).convolution(img);
}

QString GaussianBlurFilter::getName() const
{
    return "Gaussian Blur";
}

int GaussianBlurFilter::getMaxSize() const
{
    return 5;
}

double GaussianBlurFilter::getNormFactor() const
{
    return 5.0;
}
