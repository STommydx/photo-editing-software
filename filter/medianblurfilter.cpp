#include "medianblurfilter.h"
#include "avl.h"
#include "imageutil.h"

MedianBlurFilter::MedianBlurFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString MedianBlurFilter::getName() const
{
    return "Median Blur";
}

int MedianBlurFilter::getMaxSize() const
{
    return 5;
}

QImage MedianBlurFilter::apply(const QImage &img, int size) const
{
    QImage newImage{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        AVL<int> red, green, blue;
        int lox = qMax(0, i - size + 1);
        int hix = qMin(i + size - 1, img.height() - 1);
        for (int dy=0;dy<size;dy++) for (int x=lox;x<=hix;x++) {
            QRgb pix = *ImageUtil::getPixel(img, x, dy);
            red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix));
        }
        for (int j=0;j<img.width();j++) {
            *ImageUtil::getPixel(newImage, i, j) = qRgba(red.find_median(), green.find_median(), blue.find_median(), qAlpha(*ImageUtil::getPixel(img, i, j)));
            if (j + size < img.width()) for (int x=lox;x<=hix;x++) {
                QRgb pix = *ImageUtil::getPixel(img, x, j + size);
                red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix));
            }
            if (j - size + 1 >= 0) for (int x=lox;x<=hix;x++) {
                QRgb pix = *ImageUtil::getPixel(img, x, j - size + 1);
                red.erase(qRed(pix)); green.erase(qGreen(pix)); blue.erase(qBlue(pix));
            }
        }
    }
    emit progressUpdated(img.height());
    return newImage;
}
