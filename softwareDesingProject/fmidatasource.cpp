#include "fmidatasource.h"


FmiDataSource::FmiDataSource(QObject* parent) : IDataSource(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FmiDataSource::downloadCompleted);
    firstFetchHandled_ = true;
    source_ = "temperature";
    startTime_ = QDateTime::currentDateTime();
    endTime_ = QDateTime::currentDateTime();
    location_ = "Viitasaari";
}

FmiDataSource::~FmiDataSource()
{
    delete network_;
    delete parser_;
}

void FmiDataSource::setSearchParameter(const QString param)
{
    source_ = param;
}

void FmiDataSource::makeRequest()
{
    dataBuffer_.clear();
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    bool startTimeInPast = (currentTime > startTime_);
    bool endTimeInPast = (currentTime > endTime_);
    /* Fetch both from observations and forecast */
    if(!endTimeInPast and startTimeInPast){
        firstFetchHandled_ = false;
        QUrl urlPast = buildFMIURL(false, startTime_.toString(Qt::ISODate), currentTime.toString(Qt::ISODate));
        network_->get(QNetworkRequest(urlPast));
    }
    /* Fetch from observations */
    else if(startTimeInPast and endTimeInPast){
        firstFetchHandled_ = true;
        QUrl url = buildFMIURL(false, startTime_.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
        network_->get(QNetworkRequest(url));
    }
    /* Fetch from forecasts */
    else {
        firstFetchHandled_ = true;
        QUrl url = buildFMIURL(true, startTime_.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
        network_->get(QNetworkRequest(url));
    }
}

void FmiDataSource::setLocation(const QString location)
{
    location_ = location;
}

void FmiDataSource::setTimeWindow(const QString startTime, const QString endTime)
{
    QDateTime currentDate = QDateTime::currentDateTimeUtc();
    /* Saturate the times to the max that the API allows */
    if(currentDate.addDays(3) < QDateTime::fromString(endTime, Qt::ISODate)){
        endTime_ = currentDate.addDays(3);
    }
    else
    {
        endTime_ = QDateTime::fromString(endTime, Qt::ISODate);
    }
    startTime_ = QDateTime::fromString(startTime, Qt::ISODate);
}

QUrl FmiDataSource::buildFMIURL(bool forecast, QString startTime, QString endTime)
{
    QUrl fetchURL(QString("https://opendata.fmi.fi/wfs"));
    QUrlQuery query;
    QDateTime currentDate = QDateTime::currentDateTimeUtc();
    if(forecast)
    {
        query = FMI_QUERY_FORECAST;
    }
    else
    {
        /* Get temperature from daily statistics if request is longer than one week */
        if(source_ == "temperature" and currentDate.addDays(-7) > QDateTime::fromString(startTime, Qt::ISODate)){
            query = FMI_TEMP_DAILY_QUERY_OBSERVATIONS;
        }
        else
        {
            query = FMI_QUERY_OBSERVATIONS;
        }
    }


    bool fetchingFromTooFar = false;
    /* If fetching further away than the api allows */
    if(currentDate.addDays(-7) > QDateTime::fromString(startTime, Qt::ISODate))
    {
        if(source_ != "temperature")
        {
            query.addQueryItem(STARTIME, currentDate.addDays(-7).toString(Qt::ISODate));
        }
        else
        {
            query.addQueryItem(STARTIME, startTime);
        }
        fetchingFromTooFar = true;
    }
    else
    {
        query.addQueryItem(STARTIME, startTime);
    }

    query.addQueryItem(ENDTIME, endTime);

    query.addQueryItem(LOCATION, location_);
    if((!forecast) and source_ == "temperature" and fetchingFromTooFar)
    {
        query.addQueryItem("parameters", "tday");
    }
    else
    {
        query.addQueryItem("parameters", source_);
    }
    fetchURL.setQuery(query);

    return fetchURL;
}


void FmiDataSource::fetchHandler()
{
    if(firstFetchHandled_){
        DataContainer* data = new DataContainer();
        for(auto it: dataBuffer_)
        {
            data->addElement(it);
        }

        data->setType(source_);
        data->setCategory("weather");
        data->setUnit(FMI_SOURCE_TO_UNIT_MAPPING[source_]);
        emit dataParsed(data);
    }
    else{
        firstFetchHandled_ = true;
        QDateTime currentTime = QDateTime::currentDateTimeUtc();
        QUrl urlForecast = buildFMIURL(true, currentTime.toString(Qt::ISODate), endTime_.toString(Qt::ISODate));
        network_->get(QNetworkRequest(urlForecast));
    }
}


void FmiDataSource::downloadCompleted(QNetworkReply *reply)
{
    qDebug() << "Request was " << reply->request().url();

    QDomDocument doc;

    if (!doc.setContent(reply->readAll())) {
        qDebug() << "REQUEST BROKEN, most likely invalid date";
    }

    for (QDomElement m = doc.documentElement().firstChildElement(); !m.isNull(); m = m.nextSiblingElement())
    {
        QDomElement element = m.firstChildElement().firstChildElement();
        QDomElement time = element.nextSiblingElement();
        QDomElement name = time.nextSiblingElement();
        QDomElement value = name.nextSiblingElement();


        QString timeStr = time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        QPointF point;

        if(!timeStr.isEmpty() and value.text() != "NaN"){
            point.setX(dateTime.toMSecsSinceEpoch());
            /* The observation api uses different unit for this */
            if((source_ == "TotalCloudCover") & firstFetchHandled_)
            {
                point.setY(8*(value.text().toDouble())/100);
            }
            else
            {
                point.setY(value.text().toDouble());
            }
            dataBuffer_.append(point);
        }
    }

    qDebug() << "Content read OK!" << dataBuffer_.size();

    fetchHandler();


    reply->deleteLater();
}



