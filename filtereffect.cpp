#include "filtereffect.h"

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect, double normFactor, bool sizeOption, bool strengthOption) :
    name(name),
    effect(effect),
    normFactor(normFactor),
    sizeOption(sizeOption),
    strengthOption(strengthOption)
{

}

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect, double normFactor) :
    FilterEffect{name, effect, normFactor, true, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, int)> effect) :
    FilterEffect{name, [effect](const QImage &img, int size, double) { return effect(img, size); }, 0, true, false}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, double)> effect, double normFactor) :
    FilterEffect{name, [effect](const QImage &img, int, double strength) { return effect(img, strength); }, normFactor, false, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &)> effect) :
    FilterEffect{name, [effect](const QImage &img, int, double) { return effect(img); }, 0, false, false}
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
