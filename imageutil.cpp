#include "imageutil.h"

const QRgb *ImageUtil::getPixel(const QImage &img, int x, int y)
{
    return reinterpret_cast<const QRgb*>(img.scanLine(x)) + y;
}

QRgb *ImageUtil::getPixel(QImage &img, int x, int y)
{
    return reinterpret_cast<QRgb*>(img.scanLine(x)) + y;
}
