#include "fmidatasource.h"


FmiDataSource::FmiDataSource(QObject* parent) : IDataSource(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FmiDataSource::downloadCompleted);
}

FmiDataSource::~FmiDataSource()
{
    delete network_;
    delete parser_;
}

void FmiDataSource::load(QUrl url)
{
    qDebug() << "Loading with url " << url;
    network_->get(QNetworkRequest(url));
}

void FmiDataSource::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QDomDocument doc;

    DataContainer* data = new DataContainer();

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

        QString timeStr = time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        QPointF point;

        point.setX(dateTime.toMSecsSinceEpoch());
        point.setY(value.text().toDouble());

        data->addElement(point);

    }

    qDebug() << "Content read OK!";

//    for(int i = 0; i < data.length(); i++){
//        QString xVal = QString::number(data.at(i).x(), 'g', 20);
//        QString yVal = QString::number(data.at(i).y(), 'g', 20);
//        qDebug() << qPrintable(xVal) << " "
//                 << qPrintable(yVal)
//                 << Qt::endl;
//    }

    // TODO: this neds to be set automatically to correct value
    data->setType("temperature");
    // TODO: move "weather" to some constant
    data->setCategory("weater");

    reply->deleteLater();

    emit dataParsed(data);
}



