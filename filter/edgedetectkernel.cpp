#include "edgedetectkernel.h"

EdgeDetectKernel::EdgeDetectKernel(int size, QObject *parent) : ImageKernel{size, parent}
{
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        data(dx, dy) = -1;
    }
    data(0, 0) = (size * 2 - 1) * (size * 2 - 1) - 1;
}
