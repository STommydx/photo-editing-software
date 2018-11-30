#include "invertfilter.h"
#include "imageutil.h"

InvertFilter::InvertFilter(QObject *parent) : ImagePureFilter{parent} {}

QString InvertFilter::getName() const
{
    return "Invert";
}

QImage InvertFilter::apply(const QImage &img) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        QRgb pix = *ImageUtil::getPixel(img, i, j);
        *ImageUtil::getPixel(newImg, i, j) = qRgba(255 - qRed(pix), 255 - qGreen(pix), 255 - qBlue(pix), qAlpha(pix));
    }
    return newImg;
}
