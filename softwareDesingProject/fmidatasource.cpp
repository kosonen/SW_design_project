#include "fmidatasource.h"


FmiDataSource::FmiDataSource(QObject* parent) : IDataSource(parent)
{
    network_ = new QNetworkAccessManager(this);
    parser_ = new QXmlStreamReader();
    connect(network_, &QNetworkAccessManager::finished, this, &FmiDataSource::downloadCompleted);
    firstFetchHandled_ = false;
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
    qDebug() << "CURRENT TIME" << currentTime;
    qDebug() << "START TIME" << startTime_;
    qDebug() << "END TIME" << endTime_;
    bool startTimeInPast = (currentTime > startTime_);
    bool endTimeInPast = (currentTime > endTime_);
    qDebug() << "BOOLEANS: " << startTimeInPast << endTimeInPast;
    /* Fetch both from observations and forecast */
    if(!endTimeInPast and startTimeInPast){
        firstFetchHandled_ = false;
        QUrl urlPast = buildFMIURL(false, startTime_.toString(), currentTime.toString());
        network_->get(QNetworkRequest(urlPast));
        QUrl urlForecast = buildFMIURL(true, startTime_.toString(), currentTime.toString());
        network_->get(QNetworkRequest(urlForecast));
    }
    /* Fetch from observations */
    else if(startTimeInPast and endTimeInPast){
        firstFetchHandled_ = true;
        QUrl url = buildFMIURL(false, startTime_.toString(), endTime_.toString());
        network_->get(QNetworkRequest(url));
    }
    /* Fetch from forecasts */
    else {
        firstFetchHandled_ = true;
        qDebug() << "TIMES: " << startTime_.toString() << Qt::endl;
        QUrl url = buildFMIURL(true, startTime_.toString(), endTime_.toString());
        network_->get(QNetworkRequest(url));
    }
}

void FmiDataSource::setLocation(QString location)
{
    queryParameters_[LOCATION] = location;
}

void FmiDataSource::setTimeWindow(QString startTime, QString endTime)
{
    qDebug() << startTime << endTime;
    startTime_ = QDateTime::fromString(startTime, Qt::ISODate);
    endTime_ = QDateTime::fromString(endTime, Qt::ISODate);
}

QUrl FmiDataSource::buildFMIURL(bool forecast, QString startTime, QString endTime)
{
    QUrl fetchURL(QString("https://opendata.fmi.fi/wfs"));
    QUrlQuery query;
    if(forecast)
    {
        query = FMI_QUERY_FORECAST;
    }
    else
    {
        query = FMI_QUERY_OBSERVATIONS;
    }

    query.addQueryItem(STARTIME, startTime);
    query.addQueryItem(ENDTIME,endTime);


    QHashIterator<QString,QString> i (queryParameters_);

    while(i.hasNext())
    {
        i.next();
        query.addQueryItem(i.key(), i.value());
    }
    query.addQueryItem("parameters", source_);
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

        firstFetchHandled_ = false;

        // TODO: this neds to be set automatically to correct value
        data->setType("temperature");
        // TODO: move "weather" to some constant
        data->setCategory("weather");

        emit dataParsed(data);
    }
    else{
        firstFetchHandled_ = true;
    }
}

void FmiDataSource::downloadCompleted(QNetworkReply *reply)
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

        QString timeStr = time.text();
        QDateTime dateTime = QDateTime::fromString(timeStr, Qt::ISODate);
        QPointF point;

        if(value.text().toLower() != "nan"){
            point.setX(dateTime.toMSecsSinceEpoch());
            point.setY(value.text().toDouble());

            dataBuffer_.append(point);
        }
    }

    qDebug() << "Content read OK!";

//    for(int i = 0; i < data.length(); i++){
//        QString xVal = QString::number(data.at(i).x(), 'g', 20);
//        QString yVal = QString::number(data.at(i).y(), 'g', 20);
//        qDebug() << qPrintable(xVal) << " "
//                 << qPrintable(yVal)
//                 << Qt::endl;
//    }

    reply->deleteLater();

    fetchHandler();
}



