#include "datarequestsettings.h"

DataRequestSettings::DataRequestSettings() : m_location(""), m_dataSources({}),
                                            m_startTime(""), m_endTime("")
{

}

void DataRequestSettings::setLocation(QString location)
{
    m_location = location;
}

QString DataRequestSettings::getLocation()
{
    return m_location;
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
    m_startTime = startTime;
    m_endTime = endTime;
}

QString DataRequestSettings::getStartTime()
{
    return m_startTime;
}

QString DataRequestSettings::getEndTime()
{
    return m_endTime;
}
