#ifndef EDGEHIGHLIGHTFILTER_H
#define EDGEHIGHLIGHTFILTER_H

#include "imagesizefilter.h"

class EdgeHighlightFilter : public ImageSizeFilter
{
public:
    virtual QString getName() const override;
    virtual int getMaxSize() const override;
    virtual QImage apply(const QImage &img, int size) const override;
};

#endif // EDGEHIGHLIGHTFILTER_H
