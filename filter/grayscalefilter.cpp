/**
 * @class GrayscaleFilter
 * @brief The GrayscaleFilter class represents a grayscale filter.
 *
 * It average out the values of all red, green and blue channels and produces a grayscale image.
 */

#include "grayscalefilter.h"
#include "utils/imageutil.h"

/**
 * @brief Constructs a grayscale filter with the given parent
 * @param parent the parent @c QObject
 */
GrayscaleFilter::GrayscaleFilter(QObject *parent) : ImagePureFilter{parent} {}

QString GrayscaleFilter::getName() const
{
    return "Grayscale";
}

QImage GrayscaleFilter::apply(const QImage &img) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            QRgb pix = *ImageUtil::getPixel(img, i, j);
            int avg = (qRed(pix) + qGreen(pix) + qBlue(pix)) / 3; // calculate the brightness by averaging the 3 channels
            *ImageUtil::getPixel(newImg, i, j) = qRgba(avg, avg, avg, qAlpha(pix));
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
