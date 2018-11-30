#include "pixelizefilter.h"
#include "imageutil.h"

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
    for (int i=0;i<img.height();i+=size) for (int j=0;j<img.width();j+=size) {
        int rsum = 0, gsum = 0, bsum = 0, asum = 0;
        int normFact = 0;
        for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
            int nx = i + dx, ny = j + dy;
            if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue;
            normFact++;
            QRgb pix = *ImageUtil::getPixel(img, nx, ny);
            rsum += qRed(pix); gsum += qGreen(pix); bsum += qBlue(pix); asum += qAlpha(pix);
        }
        QRgb res = qRgba(rsum / normFact, gsum / normFact, bsum / normFact, asum / normFact);
        for (int dx=0;dx<size;dx++) for (int dy=0;dy<size;dy++) {
            int nx = i + dx, ny = j + dy;
            if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue;
            *ImageUtil::getPixel(newImg, i+dx, j+dy) = res;
        }
    }
    return newImg;
}
