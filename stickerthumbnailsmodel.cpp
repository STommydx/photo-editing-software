/**
  * @class StickerThumbnailsModel
  * @brief The model of the sticker panel
  *
  * This class provides the interface to retreive the paths to all sticker items' svg.
  */
#include "stickerthumbnailsmodel.h"

#include <QDir>

/**
 * @brief Base directory of the sticker folder
 */
const QString StickerThumbnailsModel::BASE_PATH = ":/stickers/assets/img/1/";

/**
 * @brief Construct a StickerThumbnailsModel with the given @a parent item
 *
 * Initialize the paths list by reading the all the entry from the base directory
 *
 * @param parent The UI of that owns this model
 */
StickerThumbnailsModel::StickerThumbnailsModel(QObject *parent) :
    QAbstractTableModel(parent),
    paths(QDir(BASE_PATH).entryList())
{
}

/**
 * @brief Returns the total number of rows of the view
 * @param parent
 * @return the total number of rows of the view
 */
int StickerThumbnailsModel::rowCount(const QModelIndex &parent) const
{
    return (paths.size() + 1) / 2;
}

/**
 * @brief Returns the total number of columns of the view
 * @param parent
 * @return the total number of columns of the view
 */
int StickerThumbnailsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

/**
 * @brief Get the file path to the data pointed by @a index
 * @param index	the index of an item in the model
 * @param role
 * @return the file path to the data pointed by @a index
 */
QVariant StickerThumbnailsModel::data(const QModelIndex &index, int role) const
{
    int i = index.row() * 2 + index.column();

    if (i >= paths.size() || role != Qt::DisplayRole)
            return QVariant();

    QString path = paths.at(i);
    return QString(BASE_PATH + path);
}
