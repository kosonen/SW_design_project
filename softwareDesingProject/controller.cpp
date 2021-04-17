#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent):
    QObject(parent),
    m_settings(nullptr),
    m_model(nullptr),
    m_updateTimer(),
    m_saveManager(),
    m_error("")
{
    connect(&m_updateTimer, &QTimer::timeout, this, &Controller::requestData);

    // Disable auto update by default
    setAutomaticUpdate(false);
}

bool Controller::requestData()
{
    m_error = "";
    if (m_model == nullptr)
    {
        return false;
    }
    SettingsCheck SC_Check = checkSettings();
    handleSettingCheck(SC_Check);

    if(SC_Check == SC_OK ||
            SC_Check == SC_NoForecastForHydro ||
            SC_Check == SC_NoForecastForNuclear ||
            SC_Check == SC_NoForecastForUnidentifiedSource)
    {
        return m_model->update(*m_settings);
    }
    else{
        qDebug() << "Invalid settings. Request denied";
        return false;
    }

}

void Controller::setLocation(QString value)
{
    qDebug() <<"location: " << value;
    m_settings->setLocation(value);
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
    m_settings->setDatasources(sources);
}

void Controller::setTimeWindow(QString startTime, QString endTime)
{
    qDebug() << "Start Time " << startTime << " End Time " << endTime;
    m_settings->setTimeWindow(startTime, endTime);
}

void Controller::setWeatherType(QString newType)
{
    m_model->setWeatherType(newType);
}

void Controller::setElectricityType(QString newType)
{
    m_model->setElectricityType(newType);
}

void Controller::setAutomaticUpdate(bool status)
{
    m_updateTimer.stop();

    if (status)
    {
        m_updateTimer.start(10000);
    }
}

bool Controller::loadData(QString filePath)
{
    DataContainer* data = new DataContainer();

    m_saveManager.add("settings", m_settings);
    m_saveManager.add("data", data);
    m_saveManager.load(filePath);

    m_model->updateSeries(data);

//    qDebug() << data->serialize();
//    qDebug() << m_settings->serialize();

    return true;
}

bool Controller::saveData(QString filePath, QString dataSource)
{
    qDebug() << "SAVING! " << dataSource << " to "  << filePath;

    DataContainer* data = m_model->getData(dataSource);

    if (data != nullptr)
    {
        qDebug() << "GOT DATA!";
        m_saveManager.add("settings", m_settings);
        m_saveManager.add("data", data);
        m_saveManager.save(filePath);

        return true;
    }

    return false;
}


QString Controller::getPopupError()
{
    if(m_error == "")
    {
        return "";
    }
    else{
        return m_error;
    }
}

void Controller::setModel(Model* model)
{
    m_model = model;
}

void Controller::setSettings(Settings *settings)
{
    m_settings = settings;
}

SettingsCheck Controller::checkSettings()
{
    QDateTime start = QDateTime::fromString(m_settings->getStartTime(), Qt::ISODate);
    QDateTime end = QDateTime::fromString(m_settings->getEndTime(), Qt::ISODate);
    SettingsCheck retVal = SC_OK;
    if(start > end)
    {
        qDebug() << "Start time is later than end time!!!";
        retVal = SC_StartTimeGreaterThanEnd;
    }
    if(m_settings->getDatasources().isEmpty())
    {
        retVal = SC_NoSources;
    }
    QDateTime currentDateTime = getCurrentDate();
    for(QString src : m_settings->getDatasources())
    {
        if(retVal != SC_OK)
        {
            break;
        }
        if(end > currentDateTime)
        {
            if(NO_FORECAST_SOURCES.contains(src))
            {
                if(src == "Nuclear power")
                {
                    retVal = SC_NoForecastForNuclear;
                }
                else if(src == "Hydro power")
                {
                    retVal = SC_NoForecastForHydro;
                }
                else
                {
                    retVal = SC_NoForecastForUnidentifiedSource;
                }
            }
        }
    }
    return retVal;

}

void Controller::handleSettingCheck(SettingsCheck settingsStatus)
{
    switch (settingsStatus) {
        case SC_StartTimeGreaterThanEnd:
            m_error = ("Start time is greater than end time. Request denied");
            break;
        case SC_NoSources:
            m_error = ("No sources to fetch found. Request denied");
            break;
        case SC_NoForecastForHydro:
            m_error =("No forecast for hydro power. Request for other souces still send");
            break;
        case SC_NoForecastForNuclear:
            m_error =("No forecast for nuclear power. Request for other sources still send");
            break;
        case SC_NoForecastForUnidentifiedSource:
            m_error =("No forecast for unidentified source. Request for other sources still send");
            break;
        default:
            break;
    }
}

QDateTime Controller::getCurrentDate()
{
    return QDateTime::currentDateTime();
}
