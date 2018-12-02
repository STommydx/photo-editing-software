/**
 * @class ImageStrengthFilter
 * @brief The ImageStrengthFilter class provides a base class for filters with only strength option.
 *
 * The abstract class provides default size settings to map the strength only filter to the parent ImageFilter.
 * Subclass of this class are required to implement ImageStrengthFilter::apply(const QImage &, double) const instead of the original apply function.
 */

#include "imagestrengthfilter.h"

/**
 * @brief Constructs an image filter with only strength option with the give @a parent
 * @param parent the parent @c QObject
 */
ImageStrengthFilter::ImageStrengthFilter(QObject *parent) : ImageFilter{parent} {}

/**
 * @overload
 */
QImage ImageStrengthFilter::apply(const QImage &img, int, double strength) const
{
    return apply(img, strength);
}

int ImageStrengthFilter::getMaxSize() const
{
    return 10;
}

bool ImageStrengthFilter::sizeEnabled() const
{
    return false;
}


/**
 * @fn QImage ImageStrengthFilter::apply(const QImage &, double) const
 * @brief Apply the filter to the image given.
 *
 * This function defines the actual implementation of the filter.
 *
 * @param img the image to be filtered
 * @param strength the strength option of the filter
 */
