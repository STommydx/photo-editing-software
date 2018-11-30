#ifndef EDGEDETECTKERNEL_H
#define EDGEDETECTKERNEL_H

#include <QObject>

#include "imagekernel.h"

class EdgeDetectKernel : public ImageKernel
{
    Q_OBJECT
public:
    explicit EdgeDetectKernel(int size = 2, QObject *parent = nullptr);

};

#endif // EDGEDETECTKERNEL_H
