#include "api.h"

#include <QNetworkReply>
#include <QDomDocument>

API::API(QObject *parent) : QObject(parent)
{
    network = new QNetworkAccessManager(this);
    parser = new QXmlStreamReader();
    connect(network, &QNetworkAccessManager::finished, this, &API::downloadCompleted);
}

void API::load(const QString &url)
{
    qDebug() << "Loading with url " << url;
    network->get(QNetworkRequest(url));
}

QVector<QPair<QString, QString>> API::getData()
{
    return data;
}

void API::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QDomDocument doc;

    if (!doc.setContent(reply->readAll())) {
        return;
    }

    for (QDomElement m = doc.documentElement().firstChildElement(); !m.isNull(); m = m.nextSiblingElement())
    {
        QDomElement element = m.firstChildElement().firstChildElement();
        QDomElement time = element.nextSiblingElement();
        QDomElement name = time.nextSiblingElement();
        QDomElement value = name.nextSiblingElement();
        qDebug() << qPrintable(time.tagName()) << ": " << time.text() << Qt::endl;
        qDebug() << qPrintable(name.tagName()) << ": " << name.text() << Qt::endl;
        qDebug() << qPrintable(value.tagName()) << ": " << value.text() << Qt::endl;
    }

    qDebug() << "Content read OK!";

    reply->deleteLater();
}
