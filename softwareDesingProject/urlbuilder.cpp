#include "urlbuilder.h"
#include "defines.h"
#include "datarequestsettings.h"
#include <QHash>
#include <QString>
#include <QHashIterator>
#include <QUrlQuery>
#include <QDebug>
#include <QDateTime>

URLBuilder* URLBuilder::s_urlBuilder = nullptr;

URLBuilder::~URLBuilder()
{
    s_urlBuilder = nullptr;
}

URLBuilder *URLBuilder::getInstance()
{
    if(s_urlBuilder == nullptr)
    {
        s_urlBuilder = new URLBuilder;
    }
    return  s_urlBuilder;
}

bool URLBuilder::buildFMIURL(DataRequestSettings &settings, QUrl &url, QString source)
{
    QUrl fetchURL(QString("https://opendata.fmi.fi/wfs"));

    QHash<QString, QString> params = settings.getParams();
    QHashIterator<QString,QString> i (params);



    QUrlQuery query = getBaseQuery(settings.getStartTime(), settings.getEndTime());

    while(i.hasNext())
    {
        i.next();
        query.addQueryItem(i.key(), i.value());
    }
    query.addQueryItem("parameters", source);
    fetchURL.setQuery(query);
    url=fetchURL;
    return true;
}

bool URLBuilder::buildFingridURL(DataRequestSettings &settings, QUrl &url, QString source)
{
   //QUrl fetchURL(QString("https://api.fingrid.fi/v1/variable"));
    QHash<QString, QString> params = settings.getParams();
    QString id = source;
    QUrlQuery query;
    QHashIterator<QString, QString> i(params);
    while(i.hasNext())
    {
        i.next();
      //  qDebug() << "key " << i.key() << " value " << i.value();
       /* if(CONSUMPTION_OPTION_TO_MODEL_MAPPING.contains(i.key()))
        {
            id = CONSUMPTION_OPTION_TO_MODEL_MAPPING[i.key()];
        }*/
        if(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING.contains(i.key()))
        {
            query.addQueryItem(FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING[i.key()], i.value());
        }

    }
    //qDebug() << "id " << id;
    QUrl fetchURL(QString("https://api.fingrid.fi/v1/" + id + "/event/xml"));
    fetchURL.setQuery(query);
    qDebug() << "fetchurl " << fetchURL;
    url = fetchURL;
    return true;
}



URLBuilder::URLBuilder()
{

}

QUrlQuery URLBuilder::getBaseQuery(const QString &startTime,const QString &endTime)
{
    qDebug() << "getBaseQuery() startStr " << startTime << " endStr " << endTime;
    QUrlQuery retVal = FMI_QUERY_FORECAST;
    qDebug() << "getBaseQuery() " <<"Start time " << QDateTime::fromString(startTime, Qt::ISODate) << " End date " << QDateTime::fromString(endTime, Qt::ISODate);
    if(QDateTime::fromString(startTime, Qt::ISODate) > QDateTime::fromString(endTime, Qt::ISODate))
    {
        retVal = FMI_QUERY_OBSERVATIONS;
    }
    qDebug() << "getBaseQuery() " << "Query: " << retVal.toString();
    return retVal;

}
