#ifndef FILTEREFFECT_H
#define FILTEREFFECT_H

#include <QImage>
#include <functional>

class FilterEffect
{
public:
    using EffectFunction = std::function<QImage(const QImage &img, int, double)>;
    FilterEffect() = default;
    FilterEffect(const QString &name, EffectFunction effect, double normFactor);
    FilterEffect(const QString &name, std::function<QImage(const QImage &, int)> effect);
    FilterEffect(const QString &name, std::function<QImage(const QImage &, double)> effect, double normFactor);
    FilterEffect(const QString &name, std::function<QImage(const QImage &)> effect);
    QImage apply(const QImage &img, int size, double strength) const;

    bool sizeEnabled() const;
    bool strengthEnabled() const;
    QString getName() const;

private:
    QString name;
    EffectFunction effect;
    double normFactor;
    bool sizeOption;
    bool strengthOption;

    FilterEffect(const QString &name, EffectFunction effect, double normFactor, bool sizeOption, bool strengthOption);

};

#endif // FILTEREFFECT_H
