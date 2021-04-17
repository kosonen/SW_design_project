#include "datarequestsettings.h"
#include "defines.h"
#include <QDebug>

#include <QJsonObject>
#include <QJsonArray>

DataRequestSettings::DataRequestSettings() : m_params({}), m_dataSources({})
{

}

void DataRequestSettings::setLocation(QString location)
{
    if(m_params.contains(LOCATION))
    {
        m_params[LOCATION] = location;
    }
    else{
        m_params.insert(LOCATION, location);
    }
}

QString DataRequestSettings::getLocation()
{
    return m_params[LOCATION];
}

void DataRequestSettings::setDatasources(QVector<QString> sources)
{
    m_dataSources = sources;
}

QVector<QString> DataRequestSettings::getDatasources()
{
    return m_dataSources;
}

void DataRequestSettings::setTimeWindow(QString startTime, QString endTime)
{
    if(m_params.contains(STARTIME))
    {
        m_params[STARTIME] = startTime;
    }
    else{
        m_params.insert(STARTIME, startTime);
    }
    if(m_params.contains(ENDTIME))
    {
        m_params[ENDTIME] = endTime;
    }
    else{
        m_params.insert(ENDTIME, endTime);
    }
}

QString DataRequestSettings::getStartTime()
{
    return m_params[STARTIME];
}

QString DataRequestSettings::getEndTime()
{
    return m_params[ENDTIME];
}

QHash<QString, QString> DataRequestSettings::getParams()
{
    QHashIterator<QString,QString> i(m_params);
    qDebug() << "getparams";
    while(i.hasNext())
    {
        i.next();
        qDebug() << "settings() key "  << i.key() << " value " << i.value();
    }
    return m_params;
}

QJsonObject DataRequestSettings::serialize()
{
    QJsonObject settingsData;
    QJsonArray list;

    settingsData["location"] = m_params[LOCATION];
    settingsData["startTime"] = m_params[STARTIME];
    settingsData["endTime"] = m_params[ENDTIME];

    for (auto e : m_dataSources)
    {
        list.append(e);
    }

    settingsData["dataSources"] = list;

    return settingsData;
}

void DataRequestSettings::deserialize(QJsonObject data)
{

}
