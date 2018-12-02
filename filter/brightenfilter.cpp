/**
 * @class BrightenFilter
 * @brief The BrightenFilter class represents a brighten filter
 *
 * The filter brighten each pixel of the image.
 * It is used to increase the overall brightness of the image.
 */

#include "brightenfilter.h"
#include <QtMath>
#include "imageutil.h"

/**
 * @brief Construct a brighten filter with the given parent
 * @param parent the parent @c QObject
 */
BrightenFilter::BrightenFilter(QObject *parent) : ImageStrengthFilter{parent} {}

QString BrightenFilter::getName() const
{
    return "Brighten";
}

double BrightenFilter::getNormFactor() const
{
    return 10.0;
}

QImage BrightenFilter::apply(const QImage &img, double strength) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            QColor &&pix = *ImageUtil::getPixel(img, i, j);
            *ImageUtil::getPixel(newImg, i, j) = pix.lighter(qFloor(strength * 100)).rgba(); // brighten each pixel
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
