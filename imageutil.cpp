#include "imageutil.h"
#include "imagekernel.h"
#include "avl.h"

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

QImage ImageUtil::medianBlur(const QImage &img, int size)
{
    QImage newImage{img};
    for (int i=0;i<img.height();i++) {
        AVL<int> red, green, blue;
        int lox = qMax(0, i - size + 1);
        int hix = qMin(i + size - 1, img.height() - 1);
        for (int dy=0;dy<size;dy++) for (int x=lox;x<=hix;x++) {
            QRgb pix = *getPixel(img, x, dy);
            red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix));
        }
        for (int j=0;j<img.width();j++) {
            *getPixel(newImage, i, j) = qRgba(red.find_median(), green.find_median(), blue.find_median(), qAlpha(*getPixel(img, i, j)));
            if (j + size < img.width()) for (int x=lox;x<=hix;x++) {
                QRgb pix = *getPixel(img, x, j + size);
                red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix));
            }
            if (j - size + 1 >= 0) for (int x=lox;x<=hix;x++) {
                QRgb pix = *getPixel(img, x, j - size + 1);
                red.erase(qRed(pix)); green.erase(qGreen(pix)); blue.erase(qBlue(pix));
            }
        }
    }
    return newImage;
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
