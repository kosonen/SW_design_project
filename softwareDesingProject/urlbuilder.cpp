#include "urlbuilder.h"
#include "defines.h"
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
    QUrlQuery query = QUrlQuery(FMI_QUERY);

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
