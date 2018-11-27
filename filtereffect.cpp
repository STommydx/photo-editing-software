#include "filtereffect.h"

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect, bool sizeOption, bool strengthOption) :
    name(name),
    effect(effect),
    sizeOption(sizeOption),
    strengthOption(strengthOption)
{

}

FilterEffect::FilterEffect(const QString &name, FilterEffect::EffectFunction effect) :
    FilterEffect{name, effect, true, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, int)> effect) :
    FilterEffect{name, [effect](const QImage &img, int size, double) { return effect(img, size); }, true, false}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &, double)> effect, int) :
    FilterEffect{name, [effect](const QImage &img, int, double strength) { return effect(img, strength); }, false, true}
{

}

FilterEffect::FilterEffect(const QString &name, std::function<QImage (const QImage &)> effect) :
    FilterEffect{name, [effect](const QImage &img, int, double) { return effect(img); }, false, true}
{

}

QImage FilterEffect::apply(const QImage &img, int size, double strength) const
{
    return effect(img, size, strength);
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
