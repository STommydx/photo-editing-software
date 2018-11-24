#include "stickerthumbnailsmodel.h"

#include <QDir>
#include <QDebug>

const QString StickerThumbnailsModel::BASE_PATH = ":/stickers/assets/img/1/";

StickerThumbnailsModel::StickerThumbnailsModel(QObject *parent) :
    QAbstractTableModel(parent),
    paths(QDir(BASE_PATH).entryList())
{
}

int StickerThumbnailsModel::rowCount(const QModelIndex &parent) const
{
    return (paths.size() + 1) / 2;
}

int StickerThumbnailsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant StickerThumbnailsModel::data(const QModelIndex &index, int role) const
{
    int i = index.row() * 2 + index.column();

    if (i >= paths.size() || role != Qt::DisplayRole)
            return QVariant();

    QString path = paths.at(i);
    return QString(BASE_PATH + path);
}
