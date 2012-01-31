#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <QFile>
#include <QDesktopServices>
#include <QStringList>

#include "collection.h"
#include "item.h"

Collection::Collection(QSharedPointer<QNetworkAccessManager> manager, QObject *parent) :
    QObject(parent), m_item(NULL), m_manager(manager)
{
    m_cacheLocation = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
}

Collection::~Collection()
{
    if (m_item)
        delete m_item;
}

void Collection::addItem(Item* item)
{
    m_item = item;
}

void Collection::addResource(QString localPath, QUrl onlinePath)
{
    m_resources.enqueue(qMakePair(localPath, onlinePath));
}

void Collection::cacheResources()
{
    if (m_resources.count() <= 0 && m_item)
        emit cachingSucceeded();
    else if (m_resources.count() > 0 && m_item) {
        m_cacheLocation.append("/").append(m_item->name());
        QDir dir;
        dir.mkpath(m_cacheLocation);
        fetchResource();
    } else
        emit cachingFailed();
}

bool Collection::isOnline()
{
    if (m_item)
        return m_item->online();
    else
        return false;
}

Item* Collection::item()
{
    return m_item;
}

void Collection::fetchResource()
{
    m_reply = m_manager->get(QNetworkRequest(m_resources.head().second));
    connect(m_reply, SIGNAL(finished()), this, SLOT(onFetchFinished()));
}

void Collection::onFetchFinished()
{
    disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFetchFinished()));
    if (m_reply->error() != QNetworkReply::NoError) {
        qDebug("reply got error: %s", qPrintable(m_reply->errorString()));
        m_reply->deleteLater();
        m_reply = 0;
        emit cachingFailed();
    } else {
        QStringList pathParts = m_resources.dequeue().first.split("/");
        QString filePath = m_cacheLocation;
        filePath.append("/");
        QString fileName = pathParts.takeLast();
        if (pathParts.size() > 0) {
            filePath.append(pathParts.join("/"));
            QDir dir;
            dir.mkpath(filePath);
        }
        QFile file(filePath + "/" + fileName);
        file.open(QIODevice::WriteOnly);
        file.write(m_reply->readAll());
        file.close();
        m_reply->deleteLater();
        m_reply = 0;
        if (m_resources.isEmpty())
            emit cachingSucceeded();
        else
            fetchResource();
    }
}

QString Collection::collectionLocation()
{
    return m_cacheLocation;
}
