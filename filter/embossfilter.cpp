#include "embossfilter.h"
#include "embosskernel.h"

EmbossFilter::EmbossFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString EmbossFilter::getName() const
{
    return "Emboss";
}

int EmbossFilter::getMaxSize() const
{
    return 5;
}

QImage EmbossFilter::apply(const QImage &img, int size) const
{
    EmbossKernel kernel{size};
    connect(&kernel, &ImageKernel::progressUpdated, this, &ImageFilter::progressUpdated);
    return kernel.convolution(img);
}
