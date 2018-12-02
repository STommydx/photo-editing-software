#ifndef STICKERTHUMBNAILSMODEL_H
#define STICKERTHUMBNAILSMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class StickerThumbnailsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    StickerThumbnailsModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    static const QString BASE_PATH;
    /**
     * @brief file paths to all svg
     */
    QStringList paths;
};

#endif // STICKERTHUMBNAILSMODEL_H
