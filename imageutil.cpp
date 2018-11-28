#include "imageutil.h"
#include "imagekernel.h"

#include <QVector>

const QRgb *ImageUtil::getPixel(const QImage &img, int x, int y)
{
    return reinterpret_cast<const QRgb*>(img.scanLine(x)) + y;
}

QRgb *ImageUtil::getPixel(QImage &img, int x, int y)
{
    return reinterpret_cast<QRgb*>(img.scanLine(x)) + y;
}

QImage ImageUtil::grayscale(const QImage &img)
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        QRgb pix = *getPixel(img, i, j);
        int avg = (qRed(pix) + qGreen(pix) + qBlue(pix)) / 3;
        *getPixel(newImg, i, j) = qRgba(avg, avg, avg, qAlpha(pix));
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

QImage ImageUtil::fastMeanBlur(const QImage &img, int size)
{
    typedef QVector<QVector<int>> QMat;
    QMat red(img.height(), QVector<int>(img.width()));
    QMat green(red), blue(red);
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        QRgb pix = *getPixel(img, i, j);
        red[i][j] = qRed(pix);
        green[i][j] = qGreen(pix);
        blue[i][j] = qBlue(pix);
    }
    for (int i=0;i<img.height();i++) for (int j=1;j<img.width();j++) {
        red[i][j] += red[i][j - 1];
        green[i][j] += green[i][j - 1];
        blue[i][j] += blue[i][j - 1];
    }
    for (int i=1;i<img.height();i++) for (int j=0;j<img.width();j++) {
        red[i][j] += red[i - 1][j];
        green[i][j] += green[i - 1][j];
        blue[i][j] += blue[i - 1][j];
    }
    QImage newImg{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        int lox = qMax(i - size + 1, 0), loy = qMax(j - size, 0);
        int hix = qMin(i + size - 1, img.height() - 1), hiy = qMin(j + size - 1, img.width() - 1);
        int normFact = (hix - lox + 1) * (hiy - loy + 1);
        int rsum = 0, gsum = 0, bsum = 0;
        rsum += red[hix][hiy]; gsum += green[hix][hiy]; bsum += blue[hix][hiy];
        if (loy > 0) { rsum -= red[hix][loy - 1]; gsum -= green[hix][loy - 1]; bsum -= blue[hix][loy - 1]; }
        if (lox > 0) { rsum -= red[lox - 1][hiy]; gsum -= green[lox - 1][hiy]; bsum -= blue[lox - 1][hiy]; }
        if (lox > 0 && loy > 0) { rsum += red[lox - 1][loy - 1]; gsum += green[lox - 1][loy - 1]; bsum += blue[lox - 1][loy - 1]; }
        *getPixel(newImg, i, j) = qRgba(rsum / normFact, gsum / normFact, bsum / normFact, qAlpha(*getPixel(img, i, j)));
    }
    return newImg;
}

QImage ImageUtil::multipassMeanBlur(const QImage &img, int size, int pass)
{
    QImage newImage{img};
    for (int i = 0; i < pass; i++) newImage = fastMeanBlur(newImage, size);
    return newImage;
}

QImage ImageUtil::sharpen(const QImage &img, int size)
{
    return ImageKernel::sharpen(size).convolution(img);
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
