#ifndef IMAGEKERNEL_H
#define IMAGEKERNEL_H

#include <QVector>
#include <QColor>
#include <QImage>

#include "imageutil.h"

class ImageKernel
{
public:
    ImageKernel(int size = 1);
    static ImageKernel meanBlur(int size = 3);
    QImage convolution(const QImage &img);

private:
    const int size;
    QVector<QVector<int>> mat;
    inline int &data(int x, int y);
    QRgb convolution(const QImage &img, int x, int y);
};

#endif // IMAGEKERNEL_H
