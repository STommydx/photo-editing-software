#include "imageutil.h"
#include "imagekernel.h"

const QRgb *ImageUtil::getPixel(const QImage &img, int x, int y)
{
    return reinterpret_cast<const QRgb*>(img.scanLine(x)) + y;
}

QRgb *ImageUtil::getPixel(QImage &img, int x, int y)
{
    return reinterpret_cast<QRgb*>(img.scanLine(x)) + y;
}

QImage ImageUtil::weirdize(const QImage &img)
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        if ((i + j) & 1) continue;
        QRgb pix = *getPixel(img, i, j);
        int avg = (qRed(pix) + qGreen(pix) + qBlue(pix)) / 3;
        *getPixel(newImg, i, j) = qRgba(avg, 255, avg, qAlpha(pix));
    }
    return newImg;
}

QImage ImageUtil::meanBlur(const QImage &img, int size)
{
    return ImageKernel::meanBlur(size).convolution(img);
}

QImage ImageUtil::gaussianBlur(const QImage &img, int size, double sd)
{
    return ImageKernel::gaussianBlur(size, sd).convolution(img);
}
