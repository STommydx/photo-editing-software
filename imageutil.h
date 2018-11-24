#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QColor>
#include <QImage>

class ImageUtil
{
public:
    ImageUtil() = delete;
    static const QRgb *getPixel(const QImage &img, int x, int y);
    static QRgb *getPixel(QImage &img, int x, int y);
    static QImage weirdize(const QImage &img);
    static QImage meanBlur(const QImage &img, int size = 3);

};

#endif // IMAGEUTIL_H
