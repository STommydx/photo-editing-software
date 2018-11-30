#ifndef INVERTFILTER_H
#define INVERTFILTER_H

#include "imagepurefilter.h"

class InvertFilter : public ImagePureFilter
{
public:
    virtual QString getName() const override;
    virtual QImage apply(const QImage &img) const override;
};

#endif // INVERTFILTER_H
