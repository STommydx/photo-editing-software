/**
 * @class EmbossKernel
 * @brief The EmbossKernel class represents a kernel for emboss filter.
 *
 * @sa EmbossFilter
 */

#include "embosskernel.h"

/**
 * @brief Construct an emboss kernel with a radius of @a size.
 *
 * An identity kernel with a dimension ( @a size * @c 2 - @c 1) * ( @a size * @c 2 - @c 1) is constructed.
 * The center pixel weight will be the 1 and all other weights will be the distance to the center cell.
 *
 * For example, the emboss kernel with @c size = @c 2 is recreated below.
 *
 *     -2 -1  0
 *     -1  1  1
 *      0  1  2
 *
 * @param size radius of the kernel
 * @param parent the parent @c QObject
 */
EmbossKernel::EmbossKernel(int size, QObject *parent) : ImageKernel{size, parent}
{
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        data(dx, dy) = dx + dy;
    }
    data(0, 0) = 1;
}
