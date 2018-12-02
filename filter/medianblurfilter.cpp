/**
 * @class MedianBlurFilter
 * @brief The MedianBlurFilter class represents a median blur filter.
 *
 * Like GaussianBlurFilter, this filter has a similar edge-preserving propoperty.
 * It has also been widely used for image processing.
 *
 * The filter is implemented using AVL with a sliding window technique.
 * With this approach, each pixel can be calculated in quasilinear time to the radius size instead of quadratic time.
 * The algorithm process the image line by line.
 * It first constructs a window of pixels for the first column.
 * The calculating the next pixel only involves adding the next column and removing the first column.
 * The median finding can be done efficiently in AVL. See AVL for details.
 *
 * @sa GaussianBlurFilter, AVL
 */

#include "medianblurfilter.h"
#include "avl.h"
#include "imageutil.h"

MedianBlurFilter::MedianBlurFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString MedianBlurFilter::getName() const
{
    return "Median Blur";
}

int MedianBlurFilter::getMaxSize() const
{
    return 10;
}

QImage MedianBlurFilter::apply(const QImage &img, int size) const
{
    QImage newImage{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        // construct the AVLs for median finding
        AVL<int> red, green, blue;
        // calculate min/max range to handle corner cases
        int lox = qMax(0, i - size + 1);
        int hix = qMin(i + size - 1, img.height() - 1);
        // insert the first window to AVL
        for (int dy=0;dy<size;dy++) for (int x=lox;x<=hix;x++) {
            QRgb pix = *ImageUtil::getPixel(img, x, dy);
            red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix));
        }
        for (int j=0;j<img.width();j++) {
            *ImageUtil::getPixel(newImage, i, j) = qRgba(red.find_median(), green.find_median(), blue.find_median(), qAlpha(*ImageUtil::getPixel(img, i, j))); // constuct the pixel using the median value

            // sliding window
            if (j + size < img.width()) for (int x=lox;x<=hix;x++) {
                QRgb pix = *ImageUtil::getPixel(img, x, j + size);
                red.insert(qRed(pix)); green.insert(qGreen(pix)); blue.insert(qBlue(pix)); // insert the next col of last col
            }
            if (j - size + 1 >= 0) for (int x=lox;x<=hix;x++) {
                QRgb pix = *ImageUtil::getPixel(img, x, j - size + 1);
                red.erase(qRed(pix)); green.erase(qGreen(pix)); blue.erase(qBlue(pix)); // remove the first col
            }
        }
    }
    emit progressUpdated(img.height());
    return newImage;
}
