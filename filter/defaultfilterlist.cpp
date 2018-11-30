#include "defaultfilterlist.h"

#include "grayscalefilter.h"
#include "brightenfilter.h"
#include "gaussianblurfilter.h"
#include "meanblurfilter.h"

DefaultFilterList::DefaultFilterList()
{
    append(new GrayscaleFilter);
    append(new BrightenFilter);
    append(new GaussianBlurFilter);
    append(new MeanBlurFilter);
}

DefaultFilterList::~DefaultFilterList()
{
    while (!empty()) delete takeLast();
}
