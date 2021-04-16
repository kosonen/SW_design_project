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
        //qDebug() << qPrintable(value.tagName()) << ": " << value.text() << Qt::endl;
        //qDebug() << qPrintable(start_time.tagName()) << ": " << start_time.text() << Qt::endl;
        //qDebug() << qPrintable(end_time.tagName()) << ": " << end_time.text() << Qt::endl;

        QString timeStr = start_time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        if(!timeStr.isEmpty() and value.text() != "NaN"){
            QPointF point;
            point.setX(dateTime.toMSecsSinceEpoch());
            point.setY(value.text().toDouble());
            dataBuffer_.append(point);
        }
    }
    qDebug() << "Content read OK!";
    reply->deleteLater();
    fetchHandler();
//    for(int i = 0; i < data.length(); i++){
//        QString xVal = QString::number(data.at(i).x(), 'g', 20);
//        QString yVal = QString::number(data.at(i).y(), 'g', 20);
//        qDebug() << qPrintable(xVal) << " "
//                 << qPrintable(yVal)
//                 << Qt::endl;
//    }
}

void FingridDataSource::fetchHandler(){
    if(previousFetchesHandled_){
        DataContainer* data = new DataContainer();
        for(auto it: dataBuffer_)
        {
            data->addElement(it);
        }
        data->setType("electricity");
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


