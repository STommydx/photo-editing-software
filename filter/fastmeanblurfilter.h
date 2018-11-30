#ifndef FASTMEANBLURFILTER_H
#define FASTMEANBLURFILTER_H

#include "imagesizefilter.h"

class FastMeanBlurFilter : public ImageSizeFilter
{
public:
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // FASTMEANBLURFILTER_H
