/**
 * @class ImageFilter
 * @brief The ImageFilter class provide a base class interface of all filters.
 *
 * This class is an abstract base class.
 * All filters should inherit this class or its subclass and implement the actual filter in ImageFilter::apply(const QImage &, int, double) const.
 * It applicable, the filters should also implement a max size and a normalization factor for the filter.
 */

#include "imagefilter.h"

/**
 * @brief Constructs an image filter with the given @a parent
 * @param parent the parent object
 */
ImageFilter::ImageFilter(QObject *parent) : QObject{parent} {}

/**
 * @brief Apply the filter to the image given for @a pass times.
 *
 * Note that this function is a wrapper to the ImageFilter::apply(const QImage &, int, double) const function.
 * The @a strength parameter of the function are not scaled to the filter, with an alternative scale of @c 0.0 to @c 1.0.
 * The current progress of filtering can be retrieved through a connection to ImageFilter::progressUpdate(int) signal.
 *
 * @param img the image to apply the filter
 * @param size the radius size option of the filter
 * @param strength the strength option of the filter, ranged from @c 0.0 to @c 1.0
 * @param pass the number of times applying the filter
 * @return the filtered image
 */
QImage ImageFilter::operator()(const QImage &img, int size, double strength, int pass) const
{
    QImage modImg{img};
    for (int i=0;i<pass;i++) modImg = apply(modImg, size, getNormFactor() * strength);
    return modImg;
}

/**
 * @brief Returns a boolean indicating whether the size option is availiable.
 * @return a boolean indicating whether the size option is availiable
 */
bool ImageFilter::sizeEnabled() const
{
    return true;
}

/**
 * @brief Returns a boolean indicating whether the strength option is availiable.
 * @return a boolean indicating whether the strength option is availiable
 */
bool ImageFilter::strengthEnabled() const
{
    return true;
}


/**
 * @fn void ImageFilter::progressUpdated(int progress) const
 * @brief The signal emitted when the filtering progress is updated
 *
 * The filter process the image in a line by line manner.
 * The progress returned is in terms of the height of the image processing.
 *
 * @sa ImageFilter::apply(const QImage &, int, double) const
 *
 * @param progress the current progress in term of the height of the image
 */

/**
 * @fn QString ImageFilter::getName() const
 * @brief Returns the name of the filter
 * @return the name of the filter
 */

/**
 * @fn int ImageFilter::getMaxSize() const
 * @brief Returns the maximum radius size that the filter can be
 * @return the maximum radius size
 */

/**
 * @fn double ImageFilter::getNormFactor() const
 * @brief Returns the normalizeation factor when applying the filter
 *
 * When applying the filter, the stength will be scaled up by this factor.
 * To be specific, if the filter is applied with a strength of @c x (ranged from @c 0.0 - @c 1.0), the actual strength when applying the filter will be ImageFilter::getNormFactor() * @c x.
 *
 * @sa void apply(const QImage &, int, double) const
 * @return the normalization factor of the image
 */

/**
 * @fn void ImageFilter::apply(const QImage &, int, double) const
 * @brief Apply the filter to the image given
 *
 * This function defines the actual implementation of the filter.
 *
 * @param img the image to be filtered
 * @param size the radius size option of the filter
 * @param strength the strength option of the filter, scaled locally to the filter
 */
