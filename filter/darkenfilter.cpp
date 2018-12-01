#include "darkenfilter.h"
#include <QtMath>
#include "imageutil.h"

DarkenFilter::DarkenFilter(QObject *parent) : ImageStrengthFilter{parent} {}

QString DarkenFilter::getName() const
{
    return "Darken";
}

double DarkenFilter::getNormFactor() const
{
    return 10.0;
}

QImage DarkenFilter::apply(const QImage &img, double strength) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            QColor pix{*ImageUtil::getPixel(img, i, j)};
            *ImageUtil::getPixel(newImg, i, j) = pix.darker(qFloor(strength * 100)).rgba();
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
