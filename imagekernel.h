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
    static ImageKernel gaussianBlur(int size = 3, double sd = 1.0);
    static ImageKernel sharpen(int size = 2);
    static ImageKernel edgeDetect(int size = 2);
    static ImageKernel emboss(int size = 2);
    QImage convolution(const QImage &img, bool normalized = true);

private:
    const int size;
    QVector<QVector<int>> mat;
    inline int &data(int x, int y);
    inline QRgb convolution(const QImage &img, int x, int y, bool normalized = true);
};

#endif // IMAGEKERNEL_H
