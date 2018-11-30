#include "sharpenfilter.h"
#include "sharpenkernel.h"

SharpenFilter::SharpenFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString SharpenFilter::getName() const
{
    return "Sharpen";
}

int SharpenFilter::getMaxSize() const
{
    return 5;
}

QImage SharpenFilter::apply(const QImage &img, int size) const
{
    SharpenKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
