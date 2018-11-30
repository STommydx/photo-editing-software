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
    static QImage invert(const QImage &img);
    static QImage darken(const QImage &img, double strength = 3.0);
    static QImage fastMeanBlur(const QImage &img, int size = 10);
    static QImage medianBlur(const QImage &img, int size = 3);
    static QImage multipassMeanBlur(const QImage &img, int size = 10, int pass = 3);
    static QImage sharpen(const QImage &img, int size = 2);
    static QImage edgeDetect(const QImage &img, int size = 2);
    static QImage emboss(const QImage &img, int size = 2);
    static QImage pixelize(const QImage &img, int size = 4);

};

#endif // IMAGEUTIL_H
