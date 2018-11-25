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
    static QImage gaussianBlur(const QImage &img, int size = 3, double stDev = 1.0);
    static QImage fastMeanBlur(const QImage &img, int size = 10);
    static QImage multipassMeanBlur(const QImage &img, int size = 10, int pass = 3);
    static QImage sharpen(const QImage &img, int size = 2);
    static QImage pixelize(const QImage &img, int size = 4);

};

#endif // IMAGEUTIL_H
