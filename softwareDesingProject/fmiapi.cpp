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

void FMIAPI::load(QUrl url)
{
    qDebug() << "Loading with url " << url;
    network_->get(QNetworkRequest(url));
}

QList<QPointF> FMIAPI::getData()
{
    return data_;
}

void FMIAPI::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QDomDocument doc;

    data_.clear();

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
        QDateTime dateTime = QDateTime::fromString(timeStr, "yyyy-MM-ddThh:mm:ssZ");
        QPointF point;

        point.setX(dateTime.toMSecsSinceEpoch());
        point.setY(value.text().toDouble());

        data_.append(point);

    }

    qDebug() << "Content read OK!";

    for(int i = 0; i < data_.length(); i++){
        QString xVal = QString::number(data_.at(i).x(), 'g', 20);
        QString yVal = QString::number(data_.at(i).y(), 'g', 20);
        qDebug() << qPrintable(xVal) << " "
                 << qPrintable(yVal)
                 << Qt::endl;
    }


    reply->deleteLater();
}



