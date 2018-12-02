/**
 * @class FastMeanBlurFilter
 * @brief The FastMeanBlurFilter class provides a more efficient implementation of the mean blur filter.
 *
 * The filter relies on the 2D prefix sum data structure instead of naively performing kernel convolution.
 * With 2D prefix sum, each pixel can be calculated in O(1) time instead of growing quadratically with the size of the kernel.
 *
 * @sa MeanBlurFilter
 */

#include "fastmeanblurfilter.h"

#include <QVector>
#include "imageutil.h"

/**
 * @brief Constructs an efficient mean blur filter
 * @param parent the parent @c QObject
 */
FastMeanBlurFilter::FastMeanBlurFilter(QObject *parent) : ImageSizeFilter{parent} {}

QString FastMeanBlurFilter::getName() const
{
    return "Mean Blur (Large Size)";
}

int FastMeanBlurFilter::getMaxSize() const
{
    return 200;
}

QImage FastMeanBlurFilter::apply(const QImage &img, int size) const
{
    emit progressUpdated(0);

    // setup 2D vector for prefix sum
    typedef QVector<QVector<int>> QMat;
    QMat red(img.height(), QVector<int>(img.width()));
    QMat green(red), blue(red);

    // calculate 2D prefix sum for each channel
    for (int i=0;i<img.height();i++) for (int j=0;j<img.width();j++) {
        QRgb pix = *ImageUtil::getPixel(img, i, j);
        red[i][j] = qRed(pix);
        green[i][j] = qGreen(pix);
        blue[i][j] = qBlue(pix);
    }
    for (int i=0;i<img.height();i++) for (int j=1;j<img.width();j++) {
        red[i][j] += red[i][j - 1];
        green[i][j] += green[i][j - 1];
        blue[i][j] += blue[i][j - 1];
    }
    for (int i=1;i<img.height();i++) for (int j=0;j<img.width();j++) {
        red[i][j] += red[i - 1][j];
        green[i][j] += green[i - 1][j];
        blue[i][j] += blue[i - 1][j];
    }

    // constuct the new image using the prefix sum
    QImage newImg{img};
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            // get the low and high bound to handle corner cases
            int lox = qMax(i - size + 1, 0), loy = qMax(j - size, 0);
            int hix = qMin(i + size - 1, img.height() - 1), hiy = qMin(j + size - 1, img.width() - 1);
            int normFact = (hix - lox + 1) * (hiy - loy + 1); // total number of pixels responsible for the sum
            int rsum = 0, gsum = 0, bsum = 0;
            // inclusion-exclusion principle - use O(1) time to calculate submatrix sum
            rsum += red[hix][hiy]; gsum += green[hix][hiy]; bsum += blue[hix][hiy];
            if (loy > 0) { rsum -= red[hix][loy - 1]; gsum -= green[hix][loy - 1]; bsum -= blue[hix][loy - 1]; }
            if (lox > 0) { rsum -= red[lox - 1][hiy]; gsum -= green[lox - 1][hiy]; bsum -= blue[lox - 1][hiy]; }
            if (lox > 0 && loy > 0) { rsum += red[lox - 1][loy - 1]; gsum += green[lox - 1][loy - 1]; bsum += blue[lox - 1][loy - 1]; }
            *ImageUtil::getPixel(newImg, i, j) = qRgba(rsum / normFact, gsum / normFact, bsum / normFact, qAlpha(*ImageUtil::getPixel(img, i, j))); // get the average and assign the pixel
        }
    }
    emit progressUpdated(img.height());
    return newImg;
}
