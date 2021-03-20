#include "fingridapi.h"
#include <QUrlQuery>

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

void FingridAPI::load(QUrl url)
{
    qDebug() << "Loading with url " << url << Qt::endl;;


    //TODO: Make these dynamic, so pass the correct stamps as arguments
    const QString start_time_value = "2021-03-14T00:00:00Z";
    const QString end_time_value   = "2021-03-15T00:00:00Z";

    const QString start_time_header = "start_time";
    const QString end_time_header   = "end_time";

    QUrlQuery query;
    query.addQueryItem(start_time_header, start_time_value);
    query.addQueryItem(end_time_header, end_time_value);
    url.setQuery(query.query());


    QNetworkRequest req(url);
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
    QString errMsg;
    QDomDocument doc;
    if (!doc.setContent(reply->readAll(), &errMsg)) {
        qDebug() << "Fingrid request BROKEN" << Qt::endl;
        qDebug() << "Error: " << errMsg << Qt::endl;
        return;
    }
    QString tmpString = doc.toString();
    qDebug() << tmpString << Qt::endl;
    for (QDomElement m = doc.documentElement().firstChildElement(); !m.isNull(); m = m.nextSiblingElement())
    {
        QDomElement value = m.firstChildElement();
        QDomElement start_time = value.nextSiblingElement();
        QDomElement end_time = start_time.nextSiblingElement();
        qDebug() << qPrintable(value.tagName()) << ": " << value.text() << Qt::endl;
        qDebug() << qPrintable(start_time.tagName()) << ": " << start_time.text() << Qt::endl;
        qDebug() << qPrintable(end_time.tagName()) << ": " << end_time.text() << Qt::endl;

    }
    qDebug() << "Content read OK!";
    reply->deleteLater();
}
