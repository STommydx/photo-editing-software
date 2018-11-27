#include "stickerthumbnailsdelegate.h"

#include <QString>
#include <QSvgRenderer>
#include <QPainter>

StickerThumbnailsDelegate::StickerThumbnailsDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),
    renderer(new QSvgRenderer())
{
}

StickerThumbnailsDelegate::~StickerThumbnailsDelegate() { delete renderer; }

void StickerThumbnailsDelegate::paint(QPainter *painter,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    QRect rect = option.rect;
    QMargins margins;
    margins += option.rect.width() * 0.1;
    rect -= margins;

    QString path = index.model()->data(index, Qt::DisplayRole).toString();
    if(!path.isEmpty()) {
        renderer->load(path);
        renderer->render(painter, rect);
    }
}

QSize StickerThumbnailsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width() * 0.8, option.rect.width() * 0.8);
}
