#ifndef PIXELIZEFILTER_H
#define PIXELIZEFILTER_H

#include "imagesizefilter.h"

class PixelizeFilter : public ImageSizeFilter
{
    Q_OBJECT
public:
    explicit PixelizeFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // PIXELIZEFILTER_H
