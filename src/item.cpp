#include "item.h"

Item::Item(QString name, QString project, QString author,
               QUrl projectUrl, QUrl startUrl, QUrl imageUrl, bool online)
{
    m_name = name;
    m_project = project;
    m_author = author;
    m_projectUrl = projectUrl;
    m_startUrl = startUrl;
    m_imageUrl = imageUrl;
    m_online = online;
}

QString Item::name()
{
    return m_name;
}

QString Item::project()
{
    return m_project;
}

QString Item::author()
{
    return m_author;
}

QUrl Item::projectUrl()
{
    return m_projectUrl;
}

QUrl Item::startUrl()
{
    return m_startUrl;
}

QUrl Item::imageUrl()
{
    return m_imageUrl;
}

bool Item::online()
{
    return m_online;
}
