#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H

#include "imagepurefilter.h"

class GrayscaleFilter : public ImagePureFilter
{
    Q_OBJECT
public:
    explicit GrayscaleFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual QImage apply(const QImage &img) const override;
};

#endif // GRAYSCALEFILTER_H
