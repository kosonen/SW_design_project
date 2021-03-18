#include "controller.h"
#include "urlbuilder.h"
#include "defines.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent), m_settings(), m_urlBuilder(nullptr), m_requestAPI()
{
    m_urlBuilder = URLBuilder::getInstance();
}

bool Controller::requestData()
{
    bool isOk = false;
    for(QString source : m_settings.getDatasources())
    {
        if(SOURCE_TO_API_MAPPING.contains(source))
        {
            QString urlString = QString();
            if(SOURCE_TO_API_MAPPING[source] == "FMI")
            {
                isOk = m_urlBuilder->buildFMIURL(m_settings, urlString);
                if(!isOk)
                {
                    qDebug() << "Failed to build FMI url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << urlString;
                m_requestAPI.load(urlString);

            }
            else if(SOURCE_TO_API_MAPPING[source] == "FINGRID")
            {
                isOk = m_urlBuilder->buildFingridURL(m_settings, urlString);
                if(!isOk)
                {
                    qDebug() << "Failed to build Fingrid url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << urlString;
                m_requestAPI.load(urlString);
            }
        }
        else
        {
            qDebug()<< "Unknown option";
            return isOk;
        }
    }
    isOk = true;
    return isOk;
}

void Controller::setLocation(QString value)
{
    qDebug() <<"location: " << value;
    m_settings.setLocation(value);
}

void Controller::setDataSources(QVector<QString> sources)
{
    for(auto str : sources)
    {
        qDebug() << "Source " << str;
    }
    m_settings.setDatasources(sources);
}

void Controller::setTimeWindow(QString startTime, QString endTime)
{
    qDebug() << "Start Time " << startTime << " End Time " << endTime;
    m_settings.setTimeWindow(startTime, endTime);
}
