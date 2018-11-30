#include "meanblurfilter.h"
#include "meankernel.h"

MeanBlurFilter::MeanBlurFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString MeanBlurFilter::getName() const
{
    return "Mean Blur";
}

int MeanBlurFilter::getMaxSize() const
{
    return 5;
}

QImage MeanBlurFilter::apply(const QImage &img, int size) const
{
    MeanKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
