#include <QtMath>

#include "imagekernel.h"

ImageKernel::ImageKernel(int size) :
    size(size),
    mat(size * 2 - 1, QVector<int>(size * 2 - 1, 0))
{
    data(0, 0) = 1;
}

ImageKernel ImageKernel::meanBlur(int size)
{
    ImageKernel kernel{size};
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        kernel.data(dx, dy) = 1;
    }
    return kernel;
}

ImageKernel ImageKernel::gaussianBlur(int size, double sd)
{
    ImageKernel kernel{size};
    const int MULTIPLIER = 1000;
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        int sqDist = dx * dx + dy * dy;
        double density = 1.0 / qSqrt(2.0 * M_PI * sd * sd) * qExp(-sqDist / 2.0 / sd / sd);
        kernel.data(dx, dy) = qFloor(density * MULTIPLIER);
    }
    return kernel;
}

ImageKernel ImageKernel::sharpen(int size)
{
    ImageKernel kernel{size};
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        kernel.data(dx, dy) = -1;
    }
    kernel.data(0, 0) = kernel.mat.size() * kernel.mat.size();
    return kernel;
}

QImage ImageKernel::convolution(const QImage &img, bool normalized)
{
    QImage newImage{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        *ImageUtil::getPixel(newImage, i, j) = convolution(img, i, j, normalized);
    }
    return newImage;
}

QRgb ImageKernel::convolution(const QImage &img, int x, int y, bool normalized)
{
    int normFact = 0;
    int rsum = 0, gsum = 0, bsum = 0;
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue;
        normFact += data(dx, dy);
        QRgb pix = *ImageUtil::getPixel(img, nx, ny);
        rsum += data(dx, dy) * qRed(pix);
        gsum += data(dx, dy) * qGreen(pix);
        bsum += data(dx, dy) * qBlue(pix);
    }
    if (normalized && normFact) {
        rsum /= normFact;
        gsum /= normFact;
        bsum /= normFact;
    }
    rsum = qBound(0, rsum, 255);
    gsum = qBound(0, gsum, 255);
    bsum = qBound(0, bsum, 255);
    return qRgba(rsum, gsum, bsum, qAlpha(*ImageUtil::getPixel(img, x, y)));
}

int &ImageKernel::data(int x, int y)
{
    return mat[x + size - 1][y + size - 1];
}
