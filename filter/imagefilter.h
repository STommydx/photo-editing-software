#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <QImage>
#include <QObject>

class ImageFilter : public QObject
{
    Q_OBJECT
public:
    explicit ImageFilter(QObject *parent = nullptr);
    virtual ~ImageFilter() = default;

    virtual QImage operator()(const QImage &img, int size, double strength, int pass = 1) const;
    virtual QImage apply(const QImage &img, int size, double strength) const = 0;
    virtual QString getName() const = 0;
    virtual int getMaxSize() const = 0;
    virtual double getNormFactor() const = 0;
    virtual bool sizeEnabled() const;
    virtual bool strengthEnabled() const;

signals:
    void progressUpdated(int progress) const;

};

#endif // IMAGEFILTER_H
