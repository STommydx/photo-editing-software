#ifndef MEDIANBLURFILTER_H
#define MEDIANBLURFILTER_H

#include "imagesizefilter.h"

class MedianBlurFilter : public ImageSizeFilter
{
public:
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // MEDIANBLURFILTER_H
