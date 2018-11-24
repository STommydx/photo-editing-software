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

QImage ImageKernel::convolution(const QImage &img)
{
    QImage newImage{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        *ImageUtil::getPixel(newImage, i, j) = convolution(img, i, j);
    }
    return newImage;
}

QRgb ImageKernel::convolution(const QImage &img, int x, int y)
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
    return qRgba(rsum / normFact, gsum / normFact, bsum / normFact, qAlpha(*ImageUtil::getPixel(img, x, y)));
}

int &ImageKernel::data(int x, int y)
{
    return mat[x + size - 1][y + size - 1];
}
