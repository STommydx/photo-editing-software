/**
 * @class DefaultFilterList
 * @brief The DefaultFilterList class provides a default list of filters.
 *
 * The list cantain the pointers to all ImageFilter included in the PES.
 * The class inherits @c QVector hence it can be used to add and change filters like normal vector.
 */
#include "defaultfilterlist.h"

#include "grayscalefilter.h"
#include "invertfilter.h"
#include "brightenfilter.h"
#include "darkenfilter.h"
#include "gaussianblurfilter.h"
#include "fastgaussianfilter.h"
#include "meanblurfilter.h"
#include "fastmeanblurfilter.h"
#include "medianblurfilter.h"
#include "sharpenfilter.h"
#include "embossfilter.h"
#include "pixelizefilter.h"
#include "edgehighlightfilter.h"

/**
 * @brief Constructs a default list of filters.
 */
DefaultFilterList::DefaultFilterList()
{
    append(new GrayscaleFilter);
    append(new InvertFilter);
    append(new BrightenFilter);
    append(new DarkenFilter);
    append(new GaussianBlurFilter);
    append(new FastGaussianFilter);
    append(new MeanBlurFilter);
    append(new FastMeanBlurFilter);
    append(new MedianBlurFilter);
    append(new SharpenFilter);
    append(new EmbossFilter);
    append(new PixelizeFilter);
    append(new EdgeHighlightFilter);
}

/**
 * @brief Destructs the filter list and all the filters inside.
 */
DefaultFilterList::~DefaultFilterList()
{
    while (!empty()) delete takeLast();
}
