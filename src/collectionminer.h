#ifndef COLLECTIONMINER_H
#define COLLECTIONMINER_H

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QDir>

class ItemModel;
class QDeclarativeView;
class Collection;

class CollectionMiner : public QObject
{
    Q_OBJECT
public:
    explicit CollectionMiner(QDeclarativeView* view, QObject *parent = 0);
    virtual ~CollectionMiner();
    void setOnline(bool online);
    void setSuffix(QString suffix);
    void setApplicationName(QString name);
    void mine();

private slots:
    void saveCollection();
    void removeCollection();

private:
    void readFile(QString filePath);
    void fillCollectionCache();

    QDir m_collectionDir;
    bool m_online;
    QString m_suffix;
    QString m_name;
    ItemModel* m_model;
    QDeclarativeView* m_view;
    QSharedPointer<QNetworkAccessManager> m_manager;
    QQueue<Collection*> m_queue;
    QList<Collection*> m_collections;
};

#endif // COLLECTIONMINER_H
