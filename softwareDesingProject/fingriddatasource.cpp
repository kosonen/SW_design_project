#include "fingriddatasource.h"
#include <QUrlQuery>

FingridDataSource::FingridDataSource(QObject* parent) : IDataSource(parent)
{
    network_ = new QNetworkAccessManager(this);
    pieModelNetwork_ = new QNetworkAccessManager(this);
    connect(network_, &QNetworkAccessManager::finished, this, &FingridDataSource::downloadCompleted);
    connect(pieModelNetwork_, &QNetworkAccessManager::finished, this, &FingridDataSource::pieModelDownloadCompleted);
    source_ = "191";
    startTime_ = QDateTime::currentDateTime().toTimeSpec(Qt::OffsetFromUTC).addDays(-3);
    endTime_ = QDateTime::currentDateTime().toTimeSpec(Qt::OffsetFromUTC).addDays(-1);
    numberOfFetches_ = 0;

}

FingridDataSource::~FingridDataSource()
{
    delete network_;
    delete pieModelNetwork_;
}

void FingridDataSource::setSearchParameter(const QString param)
{
    source_ = param;
}

void FingridDataSource::makeRequest()
{
    dataBuffer_.clear();
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    qDebug() << "CURRENT TIME" << currentTime;
    qDebug() << "START TIME" << startTime_;
    qDebug() << "END TIME" << endTime_;
    bool startTimeInPast = (currentTime > startTime_);
    bool endTimeInPast = (currentTime > endTime_);

    bool hastPastValues = !CONSUMPTION_OPTION_TO_MODEL_MAPPING[source_].first.isEmpty();
    bool hastFutureValues = !CONSUMPTION_OPTION_TO_MODEL_MAPPING[source_].second.isEmpty();

    qDebug() << "BOOLEANS: " << endTimeInPast << startTimeInPast << hastPastValues <<  hastFutureValues;
    QUrl url;
    /* Fetch both from observations and forecast */
    if(!endTimeInPast and startTimeInPast and hastPastValues and hastFutureValues){
        previousFetchesHandled_ = false;
        url = buildFingridURL(false, startTime_.toString(Qt::ISODate), currentTime.toString(Qt::ISODate));
    }
    /* Fetch from observations */
    else if(startTimeInPast and hastPastValues){
        previousFetchesHandled_ = true;
        url = buildFingridURL(false, startTime_.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
    }
    /* Fetch from forecasts */
    else {
        previousFetchesHandled_ = true;
        qDebug() << "TIMES: " << startTime_.toString() << Qt::endl;
        url = buildFingridURL(true, startTime_.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
    }
    QNetworkRequest req(url);
    req.setRawHeader(FINGRID_KEY_HEADER.toUtf8(), FINGRID_API_KEY.toUtf8());
    network_->get(QNetworkRequest(req));
}

void FingridDataSource::parseData(QDomDocument& doc, QList<QPointF>& buffer)
{
    for (QDomElement m = doc.documentElement().firstChildElement(); !m.isNull(); m = m.nextSiblingElement())
    {
        QDomElement value = m.firstChildElement();
        QDomElement start_time = value.nextSiblingElement();
        QDomElement end_time = start_time.nextSiblingElement();
        QString timeStr = start_time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        if(!timeStr.isEmpty() and value.text() != "NaN"){
            QPointF point;
            point.setX(dateTime.toMSecsSinceEpoch());
            point.setY(value.text().toDouble());
            buffer.append(point);
        }
    }
}

void FingridDataSource::parsePieModelData(QDomDocument& doc, QList<QPointF>& buffer)
{
    for (QDomElement m = doc.documentElement().firstChildElement(); !m.isNull(); m = m.nextSiblingElement())
    {
        QDomElement value = m.firstChildElement();
        QDomElement start_time = value.nextSiblingElement();
        QDomElement end_time = start_time.nextSiblingElement();
        QString timeStr = start_time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        if(!timeStr.isEmpty() and value.text() != "NaN"){
            QPointF point;
            point.setX(dateTime.toMSecsSinceEpoch());
            point.setY(value.text().toDouble());
            /* Save only the latest element */
            if(m.nextSiblingElement().isNull()){
                buffer.append(point);
            }
        }
    }
}

void FingridDataSource::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QString errMsg;
    QDomDocument doc;

    if (!doc.setContent(reply->readAll(), &errMsg)) {
        qDebug() << "Fingrid request BROKEN" << Qt::endl;
        qDebug() << "Error: " << errMsg << Qt::endl;
        return;
    }
    parseData(doc, dataBuffer_);
    qDebug() << "Content read OK!";
    reply->deleteLater();
    fetchHandler();
}

void FingridDataSource::pieModelDownloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QString errMsg;
    QDomDocument doc;

    if (!doc.setContent(reply->readAll(), &errMsg)) {
        qDebug() << "Fingrid request BROKEN" << Qt::endl;
        qDebug() << "Error: " << errMsg << Qt::endl;
        return;
    }
    parseData(doc, dataBuffer_);
    qDebug() << "Content read OK!";
    reply->deleteLater();
    pieModelFetchHandler();
}

void FingridDataSource::fetchHandler(){
    if(previousFetchesHandled_){
        DataContainer* data = new DataContainer();
        for(auto it: dataBuffer_)
        {
            data->addElement(it);
        }
        data->setType(source_);
        data->setCategory("electricity");
        emit dataParsed(data);
    }
    else{
        previousFetchesHandled_ = true;
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        QUrl url = buildFingridURL(true, currentTime.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
        QNetworkRequest req(url);
        req.setRawHeader(FINGRID_KEY_HEADER.toUtf8(), FINGRID_API_KEY.toUtf8());
        network_->get(QNetworkRequest(req));
    }
}

void FingridDataSource::pieModelFetchHandler()
{
    if(numberOfFetches_ < PRODUCTION_METHODS_FOR_PIE_MODEL.size())
    {
        numberOfFetches_++;
        QString id = CONSUMPTION_OPTION_TO_MODEL_MAPPING[PRODUCTION_METHODS_FOR_PIE_MODEL[numberOfFetches_]].first;
        QUrl url = buildFingridURL(id);
        QNetworkRequest req(url);
        req.setRawHeader(FINGRID_KEY_HEADER.toUtf8(), FINGRID_API_KEY.toUtf8());
        pieModelNetwork_->get(QNetworkRequest(req));
    }
    else
    {
        DataContainer* data = new DataContainer();
        for(auto it: pieModelDataBuffer_)
        {
            data->addElement(it);
        }
        data->setType(source_);
        data->setCategory("electricity");
        emit currentProductionReady(data);
        numberOfFetches_ = 0;
    }

}

void FingridDataSource::getCurrentProduction()
{
    numberOfFetches_ = 0;
    QString id = CONSUMPTION_OPTION_TO_MODEL_MAPPING[PRODUCTION_METHODS_FOR_PIE_MODEL[numberOfFetches_]].first;
    QUrl url = buildFingridURL(id);
    QNetworkRequest req(url);
    req.setRawHeader(FINGRID_KEY_HEADER.toUtf8(), FINGRID_API_KEY.toUtf8());
    pieModelNetwork_->get(QNetworkRequest(req));

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


QUrl FingridDataSource::buildFingridURL(bool forecast, QString startTime, QString endTime)
{
    QString id;
    if(forecast){
        id = CONSUMPTION_OPTION_TO_MODEL_MAPPING[source_].second;
    }
    else{
        id = CONSUMPTION_OPTION_TO_MODEL_MAPPING[source_].first;
    }
    QUrlQuery query;

    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[STARTIME], startTime);
    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[ENDTIME], endTime);

    QUrl fetchURL(QString("https://api.fingrid.fi/v1/variable/" + id + "/events/xml"));
    fetchURL.setQuery(query);
    qDebug() << "FINGRID URL IS: " <<  fetchURL;
    return fetchURL;
}

QUrl FingridDataSource::buildFingridURL(QString source)
{
    QUrlQuery query;
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    /* Trace back the start time two hours, it is still possible that it will
     * return two values, we must only save the latest value */
    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[STARTIME], currentTime.addSecs(-7200).toString(Qt::ISODate));
    query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[ENDTIME], currentTime.toString(Qt::ISODate));

    QUrl fetchURL(QString("https://api.fingrid.fi/v1/variable/" + source + "/events/xml"));
    fetchURL.setQuery(query);
    return fetchURL;

}


