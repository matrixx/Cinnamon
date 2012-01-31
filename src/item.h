#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QUrl>

class Item
{
public:
    Item(QString name, QString project, QString author,
           QUrl projectUrl, QUrl startUrl, QUrl imageUrl, bool online);
    QString name();
    QString project();
    QString author();
    QUrl projectUrl();
    QUrl startUrl();
    QUrl imageUrl();
    bool online();
private:
    QString m_name;
    QString m_project;
    QString m_author;
    QUrl m_projectUrl;
    QUrl m_startUrl;
    QUrl m_imageUrl;
    bool m_online;
};

#endif // ITEM_H
