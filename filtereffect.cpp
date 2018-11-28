#include "filtereffect.h"

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect, int maxSize, double normFactor, bool sizeOption, bool strengthOption) :
    name(name),
    effect(effect),
    maxSize(maxSize),
    normFactor(normFactor),
    sizeOption(sizeOption),
    strengthOption(strengthOption)
{

}

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect, int maxSize, double normFactor) :
    FilterEffect{name, effect, maxSize, normFactor, true, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, int)> effect, int maxSize) :
    FilterEffect{name, [effect](const QImage &img, int size, double) { return effect(img, size); }, maxSize, 0, true, false}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, double)> effect, double normFactor) :
    FilterEffect{name, [effect](const QImage &img, int, double strength) { return effect(img, strength); }, 10, normFactor, false, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &)> effect) :
    FilterEffect{name, [effect](const QImage &img, int, double) { return effect(img); }, 10, 0, false, false}
{

}

QImage FilterEffect::apply(const QImage &img, int size, double strength) const
{
    return effect(img, size, strength * normFactor);
}

bool FilterEffect::sizeEnabled() const
{
    return sizeOption;
}

bool FilterEffect::strengthEnabled() const
{
    return strengthOption;
}

QString FilterEffect::getName() const
{
    return name;
}

int FilterEffect::getMaxSize() const
{
    return maxSize;
}
