#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include "item.h"
#include <QAbstractListModel>

class ItemModel: public QAbstractListModel
{
    Q_OBJECT;
public:
    enum ItemRoles { NameRole = Qt::UserRole + 1,
                        ProjectRole, AuthorRole,
                       ProjectUrlRole, StartUrlRole,
                       ImageUrlRole, OnlineRole };
    ItemModel(QObject* parent = 0);

    void addItem(const Item& item);
    void insert(const Item& item, int index);
    virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    QList<Item> m_items;
};

Q_DECLARE_METATYPE(ItemModel*);

#endif // ITEMMODEL_H
