#include "itemmodel.h"

ItemModel::ItemModel(QObject* parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ProjectRole] = "project";
    roles[AuthorRole] = "author";
    roles[ProjectUrlRole] = "projecturl";
    roles[StartUrlRole] = "starturl";
    roles[ImageUrlRole] = "imageurl";
    roles[OnlineRole] = "online";
    setRoleNames(roles);
}

void ItemModel::addItem(const Item &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << item;
    endInsertRows();
}

void ItemModel::insert(const Item &item, int index)
{
    beginInsertRows(QModelIndex(), index, 0);
    m_items.insert(index, item);
    endInsertRows();
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count > m_items.size() || m_items.size() <= 0) {
        return false;
    } else {
        beginRemoveRows(QModelIndex(), row, row + count);
        for (int i = row; i < row + count; ++i) {
            m_items.removeAt(row);
        }
        endRemoveRows();
        return true;
    }
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    return m_items.count();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > m_items.count())
        return QVariant();

    Item item = m_items[index.row()];
    switch (role) {
    case NameRole:
        return item.name();
        break;
    case ProjectRole:
        return item.project();
        break;
    case AuthorRole:
        return item.author();
        break;
    case ProjectUrlRole:
        return item.projectUrl();
        break;
    case StartUrlRole:
        return item.startUrl();
        break;
    case ImageUrlRole:
        return item.imageUrl();
        break;
    case OnlineRole:
        return item.online();
        break;
    default:
        return QVariant();
    }
}
