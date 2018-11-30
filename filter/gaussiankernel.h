#ifndef GAUSSIANKERNAL_H
#define GAUSSIANKERNAL_H

#include <QObject>

#include "imagekernel.h"

class GaussianKernel : public ImageKernel
{
    Q_OBJECT
public:
    explicit GaussianKernel(int size = 3, double sd = 1.0, QObject *parent = nullptr);

};

#endif // GAUSSIANKERNAL_H
