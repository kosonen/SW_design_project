#include "urlbuilder.h"
#include "datarequestsettings.h"
#include <QHash>
#include <QString>
#include <QHashIterator>

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

bool URLBuilder::buildFMIURL(DataRequestSettings &settings, QString &urlString)
{
    QString baseURL = "https://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::hirlam::surface::point::simple";
    QHash<QString, QString> params = settings.getParams();
    QString paramString("");
    QHashIterator<QString,QString> i (params);
    while(i.hasNext())
    {
        i.next();
        paramString += "&" + i.key() + "=" +i.value();
    }
    urlString = baseURL + paramString;
    return true;
}

bool URLBuilder::buildFingridURL(const DataRequestSettings &settings, QString &urlString)
{
    return true;
}



URLBuilder::URLBuilder()
 {

}
