#include "controller.h"
#include "urlbuilder.h"

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
    m_settings.setLocation(value);
}

void Controller::setDataSources(QVector<QString> sources)
{
    m_settings.setDatasources(sources);
}

void Controller::setTimeWindow(QString startTime, QString endTime)
{
    m_settings.setTimeWindow(startTime, endTime);
}
