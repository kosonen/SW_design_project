#include "fmiapi.h"


FMIAPI::FMIAPI(QObject* parent) : API(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FMIAPI::downloadCompleted);
}

FMIAPI::~FMIAPI()
{
    delete network_;
    delete parser_;
}

void FMIAPI::load(const QString &url)
{
    qDebug() << "Loading with url " << url;
    network_->get(QNetworkRequest(url));
}

QVector<QPair<QString, QString> > FMIAPI::getData()
{
    return data_;
}

void FMIAPI::downloadCompleted(QNetworkReply *reply)
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



