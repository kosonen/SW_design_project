#include "fingridapi.h"


FingridAPI::FingridAPI(QObject* parent) : API(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FingridAPI::downloadCompleted);

}

FingridAPI::~FingridAPI()
{
    delete network_;
    delete parser_;
}

void FingridAPI::load(const QString &url)
{
    qDebug() << "Loading with url " << url;
    QNetworkRequest req{ url };
    req.setRawHeader(FINGRIDKEYHEADER.toUtf8(), FINGRIDAPIKEY.toUtf8());
    network_->get(req);

}

QList<QPointF> FingridAPI::getData()
{
    return data_;
}

void FingridAPI::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();
    QDomDocument doc;
    if (!doc.setContent(reply->readAll())) {
        qDebug() << "Fingrid request BROKEN" << Qt::endl;

        return;
    }
    QString tmpString = doc.toString();
    qDebug() << tmpString << Qt::endl;
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
