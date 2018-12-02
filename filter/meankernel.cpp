/**
 * @class MeanKernel
 * @brief The MeanKernel class represents the a kernel for mean blur filter.
 * @sa MeanBlurFilter
 */

#include "meankernel.h"

/**
 * @brief Construct an mean kernel with a radius of @a size.
 *
 * A mean kernel with a dimension ( @a size * @c 2 - @c 1) * ( @a size * @c 2 - @c 1) is constructed.
 * @param size radius of the kernel
 * @param parent the parent @c QObject
 */
MeanKernel::MeanKernel(int size, QObject *parent) :
    ImageKernel{size, parent}
{
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        data(dx, dy) = 1;
    }
}
