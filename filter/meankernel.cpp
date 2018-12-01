#include "meankernel.h"

MeanKernel::MeanKernel(int size, QObject *parent) :
    ImageKernel{size, parent}
{
    for (int dx=-size+1;dx<size;dx++) for (int dy=-size+1;dy<size;dy++) {
        data(dx, dy) = 1;
    }
}
