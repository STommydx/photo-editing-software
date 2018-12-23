#ifndef FASTGAUSSIANFILTER_H
#define FASTGAUSSIANFILTER_H

#include "filter/imagefilter.h"

class FastGaussianFilter : public ImageFilter
{
    Q_OBJECT
public:
    explicit FastGaussianFilter(QObject *parent = nullptr);
    virtual QImage apply(const QImage &img, int size, double strength) const override;
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual double getNormFactor() const override;
};

#endif // GAUSSIANBLURFILTER_H
