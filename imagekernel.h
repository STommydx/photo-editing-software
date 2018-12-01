#ifndef IMAGEKERNEL_H
#define IMAGEKERNEL_H

#include <QVector>
#include <QColor>
#include <QImage>
#include <QObject>

#include "imageutil.h"

class ImageKernel : public QObject
{
    Q_OBJECT
public:
    ImageKernel(int size = 1, QObject *parent = nullptr);
    virtual ~ImageKernel() = default;
    QImage convolution(const QImage &img, bool normalized = true);

protected:
    int &data(int x, int y);

private:
    const int size;
    QVector<QVector<int>> mat;
    inline QRgb convolution(const QImage &img, int x, int y, bool normalized = true);

signals:
    void progressUpdated(int progress);

};

#endif // IMAGEKERNEL_H
