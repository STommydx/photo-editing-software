#ifndef MEANKERNEL_H
#define MEANKERNEL_H

#include <QObject>

#include "imagekernel.h"

class MeanKernel : public ImageKernel
{
    Q_OBJECT
public:
    MeanKernel(int size = 3, QObject *parent = nullptr);
};

#endif // MEANKERNEL_H
