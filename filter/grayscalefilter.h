#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H

#include "imagepurefilter.h"

class GrayscaleFilter : public ImagePureFilter
{
public:
    virtual QString getName() const override;
    virtual QImage apply(const QImage &img) const override;
};

#endif // GRAYSCALEFILTER_H
