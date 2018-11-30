#ifndef MEANBLURFILTER_H
#define MEANBLURFILTER_H

#include "imagesizefilter.h"

class MeanBlurFilter : public ImageSizeFilter
{
    Q_OBJECT
public:
    explicit MeanBlurFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // MEANBLURFILTER_H
