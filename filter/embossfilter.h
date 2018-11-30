#ifndef EMBOSSFILTER_H
#define EMBOSSFILTER_H

#include "imagesizefilter.h"

class EmbossFilter : public ImageSizeFilter
{
public:
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // EMBOSSFILTER_H
