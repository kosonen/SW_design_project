#include "urlbuilder.h"
#include "datarequestsettings.h"
#include <QHash>
#include <QString>
#include <QHashIterator>
#include <QUrlQuery>
#include <QDebug>

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
    QUrlQuery query;

    //default query parameters
    query.addQueryItem("service", "WFS");
    query.addQueryItem("version", "2.0.0");
    query.addQueryItem("request", "getFeature");
    query.addQueryItem("storedquery_id", "fmi::forecast::hirlam::surface::point::simple");

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

bool URLBuilder::buildFingridURL(const DataRequestSettings &settings, QUrl &url, QString source)
{
    return true;
}



URLBuilder::URLBuilder()
 {

}
