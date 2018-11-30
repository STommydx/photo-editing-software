#include "sharpenfilter.h"
#include "imagekernel.h"

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
    return ImageKernel::sharpen(size).convolution(img);
}
