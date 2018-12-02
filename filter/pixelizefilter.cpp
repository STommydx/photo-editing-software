/**
 * @class PixelizeFilter
 * @brief The PixelizeFilter class represents a pixelize filter.
 */

#include "pixelizefilter.h"
#include "utils/imageutil.h"

/**
 * @brief Constructs a pixelize filter with the given parent.
 * @param parent the parent @c QObject
 */
PixelizeFilter::PixelizeFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString PixelizeFilter::getName() const
{
    return "Pixelize";
}

int PixelizeFilter::getMaxSize() const
{
    return 200;
}

QImage PixelizeFilter::apply(const QImage &img, int size) const
{
    QImage newImg{img};
    for (int i=0;i<img.height();i+=size) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j+=size) { // for each size * size square
            int rsum = 0, gsum = 0, bsum = 0, asum = 0;
            int normFact = 0;
            for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
                int nx = i + dx, ny = j + dy;
                if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue; // ignore if out of bound
                normFact++;
                QRgb pix = *ImageUtil::getPixel(img, nx, ny);
                rsum += qRed(pix); gsum += qGreen(pix); bsum += qBlue(pix); asum += qAlpha(pix); // calculate the sum of the pixels
            }
            QRgb res = qRgba(rsum / normFact, gsum / normFact, bsum / normFact, asum / normFact);
            for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
                int nx = i + dx, ny = j + dy;
                if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue; // ignore if out of bound
                *ImageUtil::getPixel(newImg, i+dx, j+dy) = res; // set the pixel to the average value
            }
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
