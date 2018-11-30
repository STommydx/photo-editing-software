#include "defaultfilterlist.h"

#include "grayscalefilter.h"
#include "invertfilter.h"
#include "brightenfilter.h"
#include "darkenfilter.h"
#include "gaussianblurfilter.h"
#include "meanblurfilter.h"
#include "fastmeanblurfilter.h"
#include "medianblurfilter.h"
#include "sharpenfilter.h"
#include "embossfilter.h"
#include "pixelizefilter.h"
#include "edgehighlightfilter.h"

DefaultFilterList::DefaultFilterList()
{
    append(new GrayscaleFilter);
    append(new InvertFilter);
    append(new BrightenFilter);
    append(new DarkenFilter);
    append(new GaussianBlurFilter);
    append(new MeanBlurFilter);
    append(new FastMeanBlurFilter);
    append(new MedianBlurFilter);
    append(new SharpenFilter);
    append(new EmbossFilter);
    append(new PixelizeFilter);
    append(new EdgeHighlightFilter);
}

DefaultFilterList::~DefaultFilterList()
{
    while (!empty()) delete takeLast();
}
