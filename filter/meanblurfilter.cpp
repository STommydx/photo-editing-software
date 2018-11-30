#include "meanblurfilter.h"
#include "imagekernel.h"

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
    return ImageKernel::meanBlur(size).convolution(img);
}
