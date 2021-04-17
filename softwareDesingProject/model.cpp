#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_dataFetcher(new DataFetcher),
    m_weatherSeries{},
    m_eleSeries{},
    m_weatherType("Temperature"),
    m_electricityType("Hydro power"),
    /*
    m_eleProductionSeries{},
    m_eleConsumptionSeries{},
    m_windProductionSeries{},
    m_nuclearProductionSeries{},
    m_hydroProductionSeries{},
    */
    m_weatherY{},
    m_elelctricityY{},
    m_start(),
    m_end(),
    m_data()
{
    connect(m_dataFetcher, &DataFetcher::dataReady, this, &Model::updateSeries);
}

QtCharts::QLineSeries *Model::getWeatherSeries() const
{
    return m_weatherSeries;
}

QtCharts::QLineSeries *Model::getElectricitySeries() const
{
    return m_eleSeries;
}

QDateTime Model::getStartTime()
{
    return m_start;
}

QDateTime Model::getEndTime()
{
    return m_end;
}

QPointF Model::getWeatherY()
{
    return m_weatherY;
}

QPointF Model::getElectricityY()
{
    return m_elelctricityY;
}

QString Model::getWeatherType()
{
    return m_weatherType;
}

QString Model::getElectricityType()
{
    return m_electricityType;
}

QPointF Model::getLimits(QList<QPointF> data)
{
    qreal top = data.at(0).y();
    qreal bottom = data.at(0).y();
    for (auto point : data)
    {
        if(point.y() > top)
        {
            top = point.y();
        }
        if(point.y() < bottom)
        {
            bottom = point.y();
        }
    }
    return QPointF(top, bottom);
}



void Model::setWeatherSeries(QtCharts::QLineSeries *weatherSeries)
{
    m_weatherSeries = weatherSeries;
    emit weatherSeriesChanged();
}

void Model::setElectricitySeries(QtCharts::QLineSeries *electricitySeries)
{
    m_eleSeries = electricitySeries;
    emit electricitySeriesChanged();
}

void Model::setStartTime(QDateTime start)
{
    m_start = start;
    emit startTimeChanged();
}

void Model::setEndTime(QDateTime end)
{
    m_end = end;
    emit endTimeChanged();
}

void Model::setWeatherY(QPointF newValue)
{
    m_weatherY = newValue;
    emit weatherYChanged();
}

void Model::setElectricityY(QPointF newValue)
{
    m_elelctricityY = newValue;
    emit electricityYChanged();
}

void Model::setWeatherType(QString newType)
{
    qDebug() << "Weather type " << newType;
    m_weatherType = newType;
    emit weatherTypeChanged();
}

void Model::setElectricityType(QString newType)
{
    m_electricityType = newType;
    emit electricityTypeChanged();
}


bool Model::update(DataRequestSettings& settings)
{
    return m_dataFetcher->fetch(settings);
}

DataContainer* Model::getData(QString key)
{
    qDebug() << "GET DATA";

    for (auto e : m_data)
    {
        qDebug() << e.first << ": " << e.second->getType();
    }

    if (m_data.count(key))
    {
        return m_data.at(key);
    }
    else
    {
        return nullptr;
    }
}

void Model::updateSeries(DataContainer* data)
{
    qDebug() << "Updating temperature graph" << Qt::endl;

    qDebug() << data->getData().size() << Qt::endl;
    if (data->getData().size() < 2)
    {
        qDebug() << "tyhjä" << Qt::endl;
        return;
    }

    setStartTime(QDateTime::fromMSecsSinceEpoch(data->getData().first().rx()));
    setEndTime(QDateTime::fromMSecsSinceEpoch(data->getData().last().rx()));

    qDebug() << data->getCategory() << "MOON TÄSSÄ" << Qt::endl;

    if(data->getCategory() == "weather")
    {
        m_weatherSeries->replace(data->getData());
        // update weatherY axis limits
        QPointF limits = getLimits(data->getData());
        qreal yTop = limits.x() + 1;
        qreal yBottom = 0;
        qDebug() << data->getType() << Qt::endl;
        if(data->getType() == "temperature")
        {
            yBottom = limits.y() - 1;
        }

        setWeatherY(QPointF(yTop, yBottom));
    }
    else if (data->getCategory() == "electricity")
    {
        qDebug() << "haaraan menöö" << Qt::endl;
        m_eleSeries->replace(data->getData());
        QPointF limits = getLimits(data->getData());
        qreal yTop = limits.x() + 10;
        qreal yBottom = 0;
        setElectricityY(QPointF(yTop, yBottom));
    }

    //m_eleSeries->replace(data->getData());

    m_data[data->getCategory()] = data;



//    delete data;
}


