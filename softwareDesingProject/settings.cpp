#include "settings.h"
#include "defines.h"
#include <QDebug>

#include <QJsonObject>
#include <QJsonArray>

Settings::Settings() : m_params({}), m_dataSources({})
{

}

void Settings::setLocation(QString location)
{
    if(m_params.contains(LOCATION))
    {
        m_params[LOCATION] = location;
    }
    else{
        m_params.insert(LOCATION, location);
    }
}

QString Settings::getLocation()
{
    return m_params[LOCATION];
}

void Settings::setDatasources(QVector<QString> sources)
{
    m_dataSources = sources;
}

QVector<QString> Settings::getDatasources()
{
    return m_dataSources;
}

void Settings::setTimeWindow(QString startTime, QString endTime)
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

QString Settings::getStartTime()
{
    return m_params[STARTIME];
}

QString Settings::getEndTime()
{
    return m_params[ENDTIME];
}

void Settings::setDataProcessing(QString method)
{
    m_params[PROCESSING] = method;
}

QString Settings::getDataProcessing()
{
    return m_params[PROCESSING];
}

QHash<QString, QString> Settings::getParams()
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

QJsonObject Settings::serialize()
{
    QJsonObject settingsData;
    QJsonArray list;

    settingsData["location"] = m_params[LOCATION];
    settingsData["startTime"] = m_params[STARTIME];
    settingsData["endTime"] = m_params[ENDTIME];
    settingsData["dataProcessing"] = m_params[PROCESSING];

    for (auto e : m_dataSources)
    {
        list.append(e);
    }

    settingsData["dataSources"] = list;

    return settingsData;
}

void Settings::deserialize(QJsonObject data)
{
    m_params[LOCATION] = data["location"].toString();
    m_params[STARTIME] = data["startTime"].toString();
    m_params[ENDTIME] = data["endTime"].toString();
    m_params[PROCESSING] = data["dataProcessing"].toString();

    m_dataSources.clear();
    QJsonArray list = data["dataSources"].toArray();

    for (int i = 0; i < list.size(); i++) {
        QString source = list[i].toString();
        m_dataSources.push_back(source);
    }
}
