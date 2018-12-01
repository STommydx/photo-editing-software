#ifndef INVERTFILTER_H
#define INVERTFILTER_H

#include "imagepurefilter.h"

class InvertFilter : public ImagePureFilter
{
    Q_OBJECT
public:
    explicit InvertFilter(QObject *parent = nullptr);
    virtual QString getName() const override;
    virtual QImage apply(const QImage &img) const override;
};

#endif // INVERTFILTER_H
