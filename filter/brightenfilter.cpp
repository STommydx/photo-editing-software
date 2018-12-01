#include "brightenfilter.h"
#include <QtMath>
#include "imageutil.h"

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
            *ImageUtil::getPixel(newImg, i, j) = pix.lighter(qFloor(strength * 100)).rgba();
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
