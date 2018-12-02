#ifndef STICKERTHUMBNAILSDELEGATE_H
#define STICKERTHUMBNAILSDELEGATE_H

#include <QAbstractItemDelegate>
#include <QSvgRenderer>

class StickerThumbnailsDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    StickerThumbnailsDelegate(QObject *parent = 0);
    ~StickerThumbnailsDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    /**
     * @brief Used to render svg
     */
    QSvgRenderer *renderer;
};

#endif // STICKERTHUMBNAILSDELEGATE_H
