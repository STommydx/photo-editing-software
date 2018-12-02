/**
 * @class ImagePureFilter
 * @brief The ImagePureFilter class provides a base class for filters with no options.
 *
 * The abstract class provides default strength and size settings to map the no option filter to the parent ImageFilter.
 * Subclass of this class are required to implement ImagePureFilter::apply(const QImage &) const instead of the original apply function.
 */

#include "imagepurefilter.h"

/**
 * @brief Constucts a filter with no options with the given @a parent
 * @param parent the QObject parent
 */
ImagePureFilter::ImagePureFilter(QObject *parent) : ImageSizeFilter{parent} {}

int ImagePureFilter::getMaxSize() const
{
    return 10;
}

bool ImagePureFilter::sizeEnabled() const
{
    return false;
}

/**
 * @overload
 */
QImage ImagePureFilter::apply(const QImage &img, int size, double strength) const
{
    return ImageSizeFilter::apply(img, size, strength);
}

/**
 * @overload
 */
QImage ImagePureFilter::apply(const QImage &img, int) const
{
    return apply(img);
}

/**
 * @fn QImage ImagePureFilter::apply(const QImage &) const
 * @brief Apply the filter to the image given.
 *
 * This function defines the actual implementation of the filter.
 *
 * @param img the image to be filtered
 */
