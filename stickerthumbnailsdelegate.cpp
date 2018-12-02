/**
  * @class StickerThumbnailsDelegate
  * @brief Display sticker thumbnails item in the side panel
  *
  * This class controls the detail of how to display sticker thumbnails.
  */

#include "stickerthumbnailsdelegate.h"

#include <QString>
#include <QSvgRenderer>
#include <QPainter>

/**
 * @brief Construct a delegate with an empty QSvgRenderer
 * @param parent Owner of this delegate
 */
StickerThumbnailsDelegate::StickerThumbnailsDelegate(QObject *parent) :
    QAbstractItemDelegate(parent),
    renderer(new QSvgRenderer())
{
}

StickerThumbnailsDelegate::~StickerThumbnailsDelegate() { delete renderer; }

/**
 * @brief Paint the thumbnail
 * @param painter
 * @param option
 * @param index Model index of the item to be paint
 */
void StickerThumbnailsDelegate::paint(QPainter *painter,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    QRect rect = option.rect;			// get rect of the view to be rendered
    QMargins margins;
    margins += option.rect.width() * 0.1;	// create a margin with 0.1 width of the item
    rect -= margins;		         	// shrink the render rect by the margin

    QString path = index.model()->data(index, Qt::DisplayRole).toString();	// retrieve file path of the sticker
    if(!path.isEmpty()) {
        renderer->load(path);
        renderer->render(painter, rect);
    }
}

QSize StickerThumbnailsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width() * 0.8, option.rect.width() * 0.8);
}
