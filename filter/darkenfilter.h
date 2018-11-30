#ifndef DARKENFILTER_H
#define DARKENFILTER_H

#include "imagestrengthfilter.h"

class DarkenFilter : public ImageStrengthFilter
{
    Q_OBJECT
public:
    explicit DarkenFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual double getNormFactor() const override;
    virtual QImage apply(const QImage &img, double strength) const override;
};

#endif // DARKENFILTER_H
