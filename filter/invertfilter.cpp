/**
 * @class InvertFilter
 * @brief The InvertFilter class represents an invert filter.
 *
 * The filter invert the colour of the image.
 */

#include "invertfilter.h"
#include "imageutil.h"

/**
 * @brief Constructs an invert filter with the given parent
 * @param parent the parent @c QObject
 */
InvertFilter::InvertFilter(QObject *parent) : ImagePureFilter{parent} {}

QString InvertFilter::getName() const
{
    return "Invert";
}

QImage InvertFilter::apply(const QImage &img) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            QRgb pix = *ImageUtil::getPixel(img, i, j);
            *ImageUtil::getPixel(newImg, i, j) = qRgba(255 - qRed(pix), 255 - qGreen(pix), 255 - qBlue(pix), qAlpha(pix)); // invert every channel
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
