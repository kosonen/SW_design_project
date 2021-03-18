#include "controller.h"
#include "urlbuilder.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent), m_settings(), m_urlBuilder(nullptr)
{
    m_urlBuilder = URLBuilder::getInstance();
}

bool Controller::requestData()
{
    QUrl url = QUrl();
    return m_urlBuilder->buildURL(m_settings, url);
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
