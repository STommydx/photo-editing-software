/**
 * @class ImageUtil
 * @brief The ImageUtil class provides utility functions to assist image processing.
 *
 * This class is only meant to be providing a set of utility functions.
 * The class is not meant to be instantiated.
 * The constructor of the class is declared deleted.
 */

#include "imageutil.h"

/**
 * @fn ImageUtil::ImageUtil()
 * @brief Deleted default constructor.
 *
 * This class cannot be instantiated by design.
 */

/**
 * @brief Get the specific pixel of an image
 *
 * A const qualified version of ImageUtil::getPixel(QImage &, int, int).
 *
 * @param img the image
 * @param x x-coordinate of the pixel
 * @param y y-coordinate of the pixel
 * @return the rgb representation of the pixel
 */
const QRgb *ImageUtil::getPixel(const QImage &img, int x, int y)
{
    return reinterpret_cast<const QRgb*>(img.scanLine(x)) + y; // cast to rgb for correct offset (specifed in Qt Doc)
}

/**
 * @brief Get the specific pixel of an image
 *
 * @param img the image
 * @param x x-coordinate of the pixel
 * @param y y-coordinate of the pixel
 * @return the rgb representaion of the pixel
 */
QRgb *ImageUtil::getPixel(QImage &img, int x, int y)
{
    return reinterpret_cast<QRgb*>(img.scanLine(x)) + y;
}
