#ifndef DEFAULTFILTERLIST_H
#define DEFAULTFILTERLIST_H

#include <QVector>

#include "imagefilter.h"

class DefaultFilterList : public QVector<ImageFilter*>
{
public:
    DefaultFilterList();
    virtual ~DefaultFilterList();
};

#endif // DEFAULTFILTERLIST_H
