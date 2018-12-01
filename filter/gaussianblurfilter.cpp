#include "gaussianblurfilter.h"
#include "gaussiankernel.h"

GaussianBlurFilter::GaussianBlurFilter(QObject *parent) : ImageFilter{parent} {}

QImage GaussianBlurFilter::apply(const QImage &img, int size, double strength) const
{
    GaussianKernel kernel{size, strength};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}

QString GaussianBlurFilter::getName() const
{
    return "Gaussian Blur";
}

int GaussianBlurFilter::getMaxSize() const
{
    return 10;
}

double GaussianBlurFilter::getNormFactor() const
{
    return 5.0;
}
