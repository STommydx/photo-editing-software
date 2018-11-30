#include "grayscalefilter.h"
#include "imageutil.h"

QString GrayscaleFilter::getName() const
{
    return "Grayscale";
}

QImage GrayscaleFilter::apply(const QImage &img) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        QRgb pix = *ImageUtil::getPixel(img, i, j);
        int avg = (qRed(pix) + qGreen(pix) + qBlue(pix)) / 3;
        *ImageUtil::getPixel(newImg, i, j) = qRgba(avg, avg, avg, qAlpha(pix));
    }
    return newImg;
}
