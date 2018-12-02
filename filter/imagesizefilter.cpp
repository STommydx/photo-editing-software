/**
 * @class ImageSizeFilter
 * @brief The ImageSizeFilter class provides a base class for filters with only size option.
 *
 * The abstract class provides default strength settings to map the size only filter to the parent ImageFilter.
 * Subclass of this class are required to implement ImageSizeFilter::apply(const QImage &, int) const instead of the original apply function.
 */

#include "imagesizefilter.h"

/**
 * @brief Constructs an image filter with only size option using @a parent
 * @param parent the parent @c QObject
 */
ImageSizeFilter::ImageSizeFilter(QObject *parent) : ImageFilter{parent} {}

/**
 * @overload
 */
QImage ImageSizeFilter::apply(const QImage &img, int size, double) const
{
    return apply(img, size);
}

double ImageSizeFilter::getNormFactor() const
{
    return 1.0;
}

bool ImageSizeFilter::strengthEnabled() const
{
    return false;
}

/**
 * @fn QImage ImageSizeFilter::apply(const QImage &, int) const
 * @brief Apply the filter to the image given.
 *
 * This function defines the actual implementation of the filter.
 *
 * @param img the image to be filtered
 * @param size the size option of the filter
 */
