/**
 * @class EdgeDetectKernel
 * @brief The EdgeDetectKernel class represents a edge detection kernel for edge highlighting filter.
 *
 * @sa EdgeHighlightFilter
 */

#include "edgedetectkernel.h"

/**
 * @brief Construct an edge detect kernel with a radius of @a size.
 *
 * An identity kernel with a dimension ( @a size * @c 2 - @c 1) * ( @a size * @c 2 - @c 1) is constructed.
 * The center pixel weight will be the total number of cells minus @c 1 and all other weights will be @c -1.
 *
 * For example, the edge detect kernel with @c size = @c 2 is recreated below.
 *
 *     -1 -1 -1
 *     -1  8 -1
 *     -1 -1 -1
 *
 * @param size radius of the kernel
 * @param parent the parent @c QObject
 */
EdgeDetectKernel::EdgeDetectKernel(int size, QObject *parent) : ImageKernel{size, parent}
{
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        data(dx, dy) = -1;
    }
    data(0, 0) = (size * 2 - 1) * (size * 2 - 1) - 1;
}
