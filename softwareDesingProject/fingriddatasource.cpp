#include "fingriddatasource.h"
#include <QUrlQuery>

FingridDataSource::FingridDataSource(QObject* parent) : IDataSource(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FingridDataSource::downloadCompleted);
    source_ = "191";
    startTime_ = QDateTime::currentDateTime().toTimeSpec(Qt::OffsetFromUTC).addDays(-3);
    endTime_ = QDateTime::currentDateTime().toTimeSpec(Qt::OffsetFromUTC).addDays(-1);

}

FingridDataSource::~FingridDataSource()
{
    delete network_;
    delete parser_;
}

void FingridDataSource::setSearchParameter(const QString param)
{
    source_ = param;
}

void FingridDataSource::makeRequest()
{

    QUrl url = buildFingridURL();
    QNetworkRequest req(url);
    req.setRawHeader(FINGRID_KEY_HEADER.toUtf8(), FINGRID_API_KEY.toUtf8());
    network_->get(req);
}

void FingridDataSource::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QString errMsg;
    QDomDocument doc;

    DataContainer* data = new DataContainer;

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

        QString timeStr = start_time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        if(!timeStr.isEmpty()){
            QPointF point;
            point.setX(dateTime.toMSecsSinceEpoch());
            point.setY(value.text().toDouble());
            data->addElement(point);
        }
    }
    qDebug() << "Content read OK!";
    reply->deleteLater();

//    for(int i = 0; i < data.length(); i++){
//        QString xVal = QString::number(data.at(i).x(), 'g', 20);
//        QString yVal = QString::number(data.at(i).y(), 'g', 20);
//        qDebug() << qPrintable(xVal) << " "
//                 << qPrintable(yVal)
//                 << Qt::endl;
//    }

    data->setCategory("electricity");

    emit dataParsed(data);
}


void FingridDataSource::setTimeWindow(QString startTime, QString endTime)
{

    if(!startTime.isEmpty()){
        startTime_ = QDateTime::fromString(startTime, Qt::ISODate);
    }
    if(!endTime.isEmpty()){
        endTime_ = QDateTime::fromString(endTime, Qt::ISODate);
    }
}


QUrl FingridDataSource::buildFingridURL()
{
    QHash<QString, QString> params;
    QString id;
    QUrlQuery query;
    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[STARTIME],
                       startTime_.toString(Qt::ISODate));

    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[ENDTIME],
                       endTime_.toString(Qt::ISODate));


    QUrl fetchURL(QString("https://api.fingrid.fi/v1/variable/" + source_ + "/event/xml"));
    fetchURL.setQuery(query);
    qDebug() << "FINGRID URL IS: " <<  fetchURL;
    return fetchURL;
}


