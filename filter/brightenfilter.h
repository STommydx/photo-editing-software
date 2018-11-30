#ifndef BRIGHTENFILTER_H
#define BRIGHTENFILTER_H

#include "imagestrengthfilter.h"

class BrightenFilter : public ImageStrengthFilter
{
    Q_OBJECT
public:
    explicit BrightenFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual double getNormFactor() const override;
    virtual QImage apply(const QImage &img, double strength) const override;
};

#endif // BRIGHTENFILTER_H
