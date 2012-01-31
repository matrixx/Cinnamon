#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QUrl>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QCoreApplication>

#include "collectionminer.h"
#include "itemmodel.h"
#include "collection.h"

CollectionMiner::CollectionMiner(QDeclarativeView* view, QObject *parent) :
    QObject(parent), m_online(false), m_view(view)
{
    m_manager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager(this));
    qDebug("initializing miner");
    m_model = new ItemModel(this);
    m_view->rootContext()->setContextProperty("itemModel", m_model);
}

CollectionMiner::~CollectionMiner()
{
    qDeleteAll(m_collections);
}

void CollectionMiner::setOnline(bool online)
{
    m_online = online;
}

void CollectionMiner::setSuffix(QString suffix)
{
    m_suffix = suffix;
}

void CollectionMiner::setApplicationName(QString name)
{
    m_name = name;
}

void CollectionMiner::mine()
{
    m_collectionDir = QDir(QString("/opt/" + m_name + "/qml/" + m_name + "/collection/"));
    qDebug("starting to mine");
    QFileInfoList entries = m_collectionDir.entryInfoList(QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Files);
    qDebug("was looking from: %s", qPrintable(m_collectionDir.path()));
    qDebug("found %d entries", entries.count());
    foreach (QFileInfo file, entries) {
        if (file.suffix() == m_suffix) {
            readFile(file.canonicalFilePath());
        }
    }
    if (!m_queue.isEmpty())
        fillCollectionCache();
}

void CollectionMiner::readFile(QString filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("Item");

    QString name = settings.value("Name").toString();
    QString project = settings.value("Project").toString();
    QString author = settings.value("Author").toString();
    QUrl projectUrl = settings.value("ProjectUrl").toUrl();
    QUrl startUrl = settings.value("StartUrl").toUrl();
    QUrl imageUrl = settings.value("ImageUrl").toUrl();
    bool online = settings.value("Online").toBool();
    settings.endGroup();

    if (!name.isEmpty() && !project.isEmpty() && !author.isEmpty()
            && !projectUrl.isEmpty() && !startUrl.isEmpty()
            && !imageUrl.isEmpty()) {
        Collection* collection = new Collection(m_manager);
        QString location = QString("/opt/" + m_name + "/qml/cinnamon/");
        if (online) {
            settings.beginGroup("Resources");
            QStringList keys = settings.allKeys();
            foreach (QString key, keys) {
                collection->addResource(key, settings.value(key).toUrl());
            }
            settings.endGroup();
            if (keys.size() > 0) {
                location = collection->collectionLocation();
                location.append("/").append(name).append("/");
            }
        }
        startUrl = QUrl(location + startUrl.toString());
        collection->addItem(new Item(name, project, author, projectUrl,
                                   startUrl, imageUrl, online));
        m_queue.enqueue(collection);
    }
}

void CollectionMiner::fillCollectionCache()
{
    connect(m_queue.head(), SIGNAL(cachingSucceeded()),
            this, SLOT(saveCollection()));
    connect(m_queue.head(), SIGNAL(cachingFailed()),
            this, SLOT(removeCollection()));
    m_queue.head()->cacheResources();
}

void CollectionMiner::saveCollection()
{
    m_collections.append(m_queue.dequeue());
    m_model->addItem(*m_collections.last()->item());
    if (m_queue.isEmpty()) {
        m_view->rootContext()->setContextProperty("itemModel", m_model);
        qDebug("model updated");
    } else {
        fillCollectionCache();
    }
}

void CollectionMiner::removeCollection()
{
    delete m_queue.dequeue();
    if (m_queue.isEmpty()) {
        m_view->rootContext()->setContextProperty("itemModel", m_model);
        qDebug("model updated");
    } else {
        fillCollectionCache();
    }
}

