#ifndef IMAGEPUREFILTER_H
#define IMAGEPUREFILTER_H

#include "imagesizefilter.h"

class ImagePureFilter : public ImageSizeFilter
{
    Q_OBJECT
public:
    explicit ImagePureFilter(QObject *parent = nullptr);
    virtual int getMaxSize() const override;
    virtual bool sizeEnabled() const override;
    virtual QImage apply(const QImage &img, int size, double strength) const override;
    virtual QImage apply(const QImage &img, int size) const override;
    virtual QImage apply(const QImage &img) const = 0;
};

#endif // IMAGEPUREFILTER_H
