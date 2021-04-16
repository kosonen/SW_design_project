#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent):
    QObject(parent),
    m_settings(),
    m_model(nullptr),
    m_updateTimer()
{
    connect(&m_updateTimer, &QTimer::timeout, this, &Controller::requestData);

    // Disable auto update by default
    setAutomaticUpdate(false);
}

bool Controller::requestData()
{
    if (m_model == nullptr)
    {
        return false;
    }

    return m_model->update(m_settings);
}

void Controller::setLocation(QString value)
{
    qDebug() <<"location: " << value;
    m_settings.setLocation(value);
}

void Controller::setDataSources(QVector<QString> sources)
{
    for(auto &str : sources)
    {
        // UI has different texts than in API's, here we map UI names to API properties.
        if(WEATHER_OPTION_TO_MODEL_MAPPING.contains(str))
        {
            str = WEATHER_OPTION_TO_MODEL_MAPPING[str];

        }
        qDebug() << "Source " << str;
    }
    m_settings.setDatasources(sources);
}

void Controller::setTimeWindow(QString startTime, QString endTime)
{
    qDebug() << "Start Time " << startTime << " End Time " << endTime;
    m_settings.setTimeWindow(startTime, endTime);
}

void Controller::setWeatherType(QString newType)
{
    m_model->setWeatherType(newType);
}

void Controller::setAutomaticUpdate(bool status)
{
    m_updateTimer.stop();

    if (status)
    {
        m_updateTimer.start(10000);
    }
}

void Controller::setModel(Model* model)
{
    m_model = model;
}
