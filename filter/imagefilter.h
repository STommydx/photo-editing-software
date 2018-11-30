#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <QImage>

class ImageFilter
{
public:
    ImageFilter() = default;
    virtual ~ImageFilter() = default;

    virtual QImage operator()(const QImage &img, int size, double strength) const;
    virtual QImage apply(const QImage &img, int size, double strength) const = 0;
    virtual QString getName() const = 0;
    virtual int getMaxSize() const = 0;
    virtual double getNormFactor() const = 0;
    virtual bool sizeEnabled() const;
    virtual bool strengthEnabled() const;

};

#endif // IMAGEFILTER_H
