#include "api.h"

#include <QNetworkReply>

API::API(QObject *parent) : QObject(parent)
{
    network = new QNetworkAccessManager(this);
    parser = new QXmlStreamReader();
    connect(network, &QNetworkAccessManager::finished, this, &API::downloadCompleted);
}

void API::load(const QString &url)
{
    network->get(QNetworkRequest(url));
}

QVector<QPair<QString, QString>> API::getData()
{
    return data;
}

void API::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    parser->addData(reply->readAll());

    while (parser->name() != "MeasurementTimeseries") {
        parser->readNext();
    }

    parser->readNextStartElement();

    while (parser->name() == "point") {
        QPair<QString, QString> point;
        parser->readNextStartElement();
        parser->readNextStartElement();
        point.first = parser->readElementText();
        parser->readNextStartElement();
        point.second = parser->readElementText();
        parser->readNextStartElement();
        parser->readNextStartElement();
        parser->readNextStartElement();
        data.push_back(point);
    }

    for (auto p : data) {
        qDebug() << p;
    }

    reply->deleteLater();
}
