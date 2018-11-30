#include "embossfilter.h"
#include "imagekernel.h"

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
    return ImageKernel::emboss(size).convolution(img);
}
