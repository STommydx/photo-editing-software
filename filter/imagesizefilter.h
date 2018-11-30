#ifndef IMAGESIZEFILTER_H
#define IMAGESIZEFILTER_H

#include "imagefilter.h"

class ImageSizeFilter : public ImageFilter
{
public:
    virtual QImage apply(const QImage &img, int size, double strength) const override;
    virtual QImage apply(const QImage &img, int size) const = 0;
    virtual double getNormFactor() const override;
    virtual bool strengthEnabled() const override;
};

#endif // IMAGESIZEFILTER_H
