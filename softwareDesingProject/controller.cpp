#include "controller.h"

#include <QDebug>

Controller::Controller(QObject *parent):
    QObject(parent),
    m_settings(),
    m_model(nullptr)
{

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

void Controller::setModel(Model* model)
{
    m_model = model;
}
