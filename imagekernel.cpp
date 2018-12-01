/**
 * @class ImageKernel
 * @brief The ImageKernel class provides the kernel representation in kernel convolution
 *
 * This class stores a 2D matrix of integers specifically for kernel convolution of @c QImage.
 */

#include <QtMath>

#include "imagekernel.h"

/**
 * @brief Construct an identity kernel with a radius of @a size.
 *
 * An identity kernel with a dimension (size * 2 - 1) * (size * 2 - 1) is constructed.
 * The center pixel weight will be @c 1 and all other weights will be @c 0.
 *
 * For example, the identity kernel with @c size = @c 2 is recreated below.
 *
 *     0 0 0
 *     0 1 0
 *     0 0 0
 *
 * @param size radius of the kernel
 * @param parent the parent @c QObject
 */
ImageKernel::ImageKernel(int size, QObject *parent) :
    QObject{parent}, // initialize the parent
    size(size), // set the kernel radius
    mat(size * 2 - 1, QVector<int>(size * 2 - 1, 0)) // initialize the 2D matrix filled with zero
{
    data(0, 0) = 1; // center pixel = 1 for identity kernel
}

/**
 * @brief Convolute the given @c QImage with the kernel.
 *
 * The convolution is done in a line by line manner.
 * The progress is emited via ImageKernel::progressUpdated(int) function.
 *
 * @param img the image to be convoluted
 * @param normalized whether the total weight should be normalized to @c 1
 * @return the convoluted image
 */
QImage ImageKernel::convolution(const QImage &img, bool normalized)
{
    QImage newImage{img}; // create new image
    for (int i=0;i<img.height();i++) {
        emit progressUpdated(i);
        for (int j=0;j<img.width();j++) {
            *ImageUtil::getPixel(newImage, i, j) = convolution(img, i, j, normalized); // calcluate and assign weighted average to each pixel
        }
    }
    emit progressUpdated(img.height());
    return newImage;
}

/**
 * @brief Calculate the weighted average of pixel \a (x, y) for convolution
 *
 * The function calculates the weighted sum of the pixel for each channel, then divided it by the total weight according to the @a normalized parameter.
 *
 * @param img the image to be convoluted
 * @param x the x coordinate of the pixel to be calculated
 * @param y the y coordinate of the pixel to be calculate
 * @param normalized whether the total weight should be normalized to @c 1
 * @return the weighted average colour for the coordinate
 */
QRgb ImageKernel::convolution(const QImage &img, int x, int y, bool normalized)
{
    int normFact = 0; // normalization factor, storing the sum of weights
    int rsum = 0, gsum = 0, bsum = 0; // sum of each colour
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) { // for a given offset in size
        int nx = x + dx, ny = y + dy; // the coordinates of the offset pixel
        if (nx < 0 || nx >= img.height() || ny < 0 || ny >= img.width()) continue; // consider next if out of bound
        normFact += data(dx, dy); // add the weight to the normalization factor
        QRgb pix = *ImageUtil::getPixel(img, nx, ny); // get the pixel
        rsum += data(dx, dy) * qRed(pix); // multiply and add to each channel
        gsum += data(dx, dy) * qGreen(pix);
        bsum += data(dx, dy) * qBlue(pix);
    }
    if (normalized && normFact) { // if normalization is required
        rsum /= normFact; // divide each sum by total weight to normalize
        gsum /= normFact;
        bsum /= normFact;
    }
    rsum = qBound(0, rsum, 255); // cap it in range [0..255] to prevent underflow or overflow
    gsum = qBound(0, gsum, 255);
    bsum = qBound(0, bsum, 255);
    return qRgba(rsum, gsum, bsum, qAlpha(*ImageUtil::getPixel(img, x, y)));
}

/**
 * @brief Get the kernel weight value in the kernel matrix
 * @param x the x-coordinate offset to the center pixel
 * @param y the y-coordinate offset to the center pixel
 * @return the weight for given offset
 */
int &ImageKernel::data(int x, int y)
{
    return mat[x + size - 1][y + size - 1]; // add back the offset for storage or access
}

/**
 * @fn void ImageKernel::progressUpdated(int progress)
 * @brief The signal emmited when the covolution progress is updated.
 * @sa ImageKernel::convolution(const QImage &, bool)
 * @param progress the progress in terms of image height
 */
