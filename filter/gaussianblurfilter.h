#ifndef GAUSSIANBLURFILTER_H
#define GAUSSIANBLURFILTER_H

#include "filter/imagefilter.h"

class GaussianBlurFilter : public ImageFilter
{
    Q_OBJECT
public:
    explicit GaussianBlurFilter(QObject *parent = nullptr);
    virtual QImage apply(const QImage &img, int size, double strength) const override;
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual double getNormFactor() const override;
};

#endif // GAUSSIANBLURFILTER_H
