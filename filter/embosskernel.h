#ifndef EMBOSSKERNEL_H
#define EMBOSSKERNEL_H

#include <QObject>

#include "imagekernel.h"

class EmbossKernel : public ImageKernel
{
    Q_OBJECT
public:
    explicit EmbossKernel(int size = 2, QObject *parent = nullptr);

};

#endif // EMBOSKERNEL_H
