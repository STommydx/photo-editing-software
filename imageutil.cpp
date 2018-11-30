#include "imageutil.h"
#include "imagekernel.h"

#include <QVector>
#include <QtMath>

const QRgb *ImageUtil::getPixel(const QImage &img, int x, int y)
{
    return reinterpret_cast<const QRgb*>(img.scanLine(x)) + y;
}

QRgb *ImageUtil::getPixel(QImage &img, int x, int y)
{
    return reinterpret_cast<QRgb*>(img.scanLine(x)) + y;
}

QImage ImageUtil::sharpen(const QImage &img, int size)
{
    return ImageKernel::sharpen(size).convolution(img);
}

QImage ImageUtil::edgeDetect(const QImage &img, int size)
{
    return ImageKernel::edgeDetect(size).convolution(img);
}

QImage ImageUtil::emboss(const QImage &img, int size)
{
    return ImageKernel::emboss(size).convolution(img);
}

QImage ImageUtil::pixelize(const QImage &img, int size)
{
    QImage newImg{img};
    for (int i=0;i<img.height();i+=size) for (int j=0;j<img.width();j+=size) {
        int rsum = 0, gsum = 0, bsum = 0, asum = 0;
        int normFact = 0;
        for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
            int nx = i + dx, ny = j + dy;
            if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue;
            normFact++;
            QRgb pix = *getPixel(img, nx, ny);
            rsum += qRed(pix); gsum += qGreen(pix); bsum += qBlue(pix); asum += qAlpha(pix);
        }
        QRgb res = qRgba(rsum / normFact, gsum / normFact, bsum / normFact, asum / normFact);
        for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
            int nx = i + dx, ny = j + dy;
            if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue;
            *getPixel(newImg, i+dx, j+dy) = res;
        }
    }
    return newImg;
}
