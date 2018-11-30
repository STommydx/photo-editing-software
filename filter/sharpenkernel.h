#ifndef SHARPENKERNEL_H
#define SHARPENKERNEL_H

#include <QObject>

#include "imagekernel.h"

class SharpenKernel : public ImageKernel
{
    Q_OBJECT
public:
    explicit SharpenKernel(int size = 2, QObject *parent = nullptr);

};

#endif // SHARPENKERNEL_H
