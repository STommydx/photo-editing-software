#ifndef IMAGESTRENGTHFILTER_H
#define IMAGESTRENGTHFILTER_H

#include "imagefilter.h"

class ImageStrengthFilter : public ImageFilter
{
    Q_OBJECT
public:
    explicit ImageStrengthFilter(QObject *parent = nullptr);
    virtual QImage apply(const QImage &img, int size, double strength) const override;
    virtual QImage apply(const QImage &img, double strength) const = 0;
    virtual int getMaxSize() const override;
    virtual bool sizeEnabled() const override;
};

#endif // IMAGESTRENGTHFILTER_H
