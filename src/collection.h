#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include <QPair>
#include <QQueue>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QUrl>

class QNetworkReply;
class Item;

class Collection : public QObject
{
    Q_OBJECT
public:
    explicit Collection(QSharedPointer<QNetworkAccessManager> manager, QObject *parent = 0);
    virtual ~Collection();
    void addItem(Item* item);
    void addResource(QString localPath, QUrl onlinePath);
    void cacheResources();
    bool isOnline();
    QString collectionLocation();
    Item* item();

signals:
    void cachingSucceeded();
    void cachingFailed();

public slots:

private slots:
    void onFetchFinished();

private:
    void fetchResource();

    Item* m_item;
    QQueue<QPair<QString, QUrl> > m_resources;

    QSharedPointer<QNetworkAccessManager> m_manager;
    QNetworkReply* m_reply;
    QString m_cacheLocation;
};

#endif // COLLECTION_H
