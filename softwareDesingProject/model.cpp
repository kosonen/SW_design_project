#include "model.h"
#include "defines.h"
#include <QPieSlice>

Model::Model(QObject *parent):
    QObject(parent),
    m_dataFetcher(new DataFetcher),
    m_weatherSeries{},
    m_eleSeries{},
    m_savedSeries{},
    m_weatherY{new QtCharts::QValueAxis},
    m_elelctricityY{new QtCharts::QValueAxis},
    m_savedY{new QtCharts::QValueAxis},
    m_pieseries(new QtCharts::QPieSeries),
    m_start(),
    m_end(),
    m_data(),
    m_hydroConsumption(""),
    m_nucklearConsumption(""),
    m_windConsumption("")
{
    connect(m_dataFetcher, &DataFetcher::dataReady, this, &Model::updateSeries);
    connect(m_dataFetcher, &DataFetcher::currentProductionReady, this, &Model::updateProductionPieModel);

}

QtCharts::QLineSeries *Model::getWeatherSeries() const
{
    return m_weatherSeries;
}

QtCharts::QLineSeries *Model::getElectricitySeries() const
{
    return m_eleSeries;
}

QtCharts::QLineSeries *Model::getSavedSeries() const
{
    return m_savedSeries;
}

QDateTime Model::getStartTime()
{
    return m_start;
}

QDateTime Model::getEndTime()
{
    return m_end;
}

QtCharts::QValueAxis* Model::getWeatherY()
{
    return m_weatherY;
}

QtCharts::QValueAxis* Model::getElectricityY()
{
    return m_elelctricityY;
}

QtCharts::QValueAxis *Model::getSavedY()
{
    return m_savedY;
}

QtCharts::QPieSeries* Model::getPieSeries() const
{
    return m_pieseries;
}

QString Model::getHydroConsumption()
{
    return m_hydroConsumption;
}

QString Model::getNucklearConsumption()
{
    return m_nucklearConsumption;
}

QString Model::getWindConsumption()
{
    return m_windConsumption;
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

void Model::setSavedSeries(QtCharts::QLineSeries *savedSeries)
{
    m_savedSeries = savedSeries;
    emit savedSeriesChanged();
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

void Model::setWeatherY(QtCharts::QValueAxis* newValue)
{
    m_weatherY = newValue;
    emit weatherYChanged();
}

void Model::setElectricityY(QtCharts::QValueAxis* newValue)
{
    m_elelctricityY = newValue;
    emit electricityYChanged();
}

void Model::setSavedY(QtCharts::QValueAxis *newValue)
{
    m_savedY = newValue;
    emit savedYChanged();
}

void Model::setPieSeries(QtCharts::QPieSeries *pieSeries)
{
    m_pieseries = pieSeries;
    emit pieSeriesChanged();
}

bool Model::update(Settings& settings)
{
    setStartTime(QDateTime::fromString(settings.getStartTime(), Qt::ISODate));
    setEndTime(QDateTime::fromString(settings.getEndTime(), Qt::ISODate));

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

    if(data->getCategory() == "weather")
    {
        m_weatherSeries->replace(data->getData());
        m_weatherY->setTitleText(data->getUnit());
        m_weatherSeries->setColor(SOURCE_TO_COLOR_MAPPING[data->getType()]);
        m_weatherSeries->setName(SOURCE_TO_NAME_MAPPING[data->getType()]);

        QPointF limits = getLimits(data->getData());
        qreal yTop = limits.x() + 1;
        qreal yBottom = 0;

        if(data->getType() == "temperature")
        {
            yBottom = limits.y() - 1;
        }

        m_weatherY->setMax(yTop);
        m_weatherY->setMin(yBottom);

    }
    else if (data->getCategory() == "electricity")
    {
        m_eleSeries->replace(data->getData());
        m_elelctricityY->setTitleText(data->getUnit());
        m_eleSeries->setColor(SOURCE_TO_COLOR_MAPPING[data->getType()]);
        m_eleSeries->setName(SOURCE_TO_NAME_MAPPING[data->getType()]);

        QPointF limits = getLimits(data->getData());
        qreal yTop = limits.x() * 1.25;
        qreal yBottom = limits.y() * 0.7;

        m_elelctricityY->setMax(yTop);
        m_elelctricityY->setMin(yBottom);
    }

    else if (data->getCategory() == "save")
    {
        m_savedSeries->replace(data->getData());
        m_savedSeries->setName("Saved " + SOURCE_TO_NAME_MAPPING[data->getType()]);

        QPointF limits = getLimits(data->getData());

        qDebug() << "data type: " << data->getType() << Qt::endl;
        if(data->getType() == "temperature" || data->getType() == "windspeedms"
                || data->getType() == "humidity" || data->getType() == "TotalCouldCover"){

            qreal yTop = limits.x() + 1;
            qreal yBottom = 0;

            if(data->getType() == "temperature")
            {
                yBottom = limits.y() - 1;
            }

            m_savedY->setMax(yTop);
            m_savedY->setMin(yBottom);
            m_savedY->setTitleText("Saved " + data->getUnit());

        }
        else {

            qreal yTop = limits.x() + 10;
            qreal yBottom = 0;

            m_savedY->setMax(yTop);
            m_savedY->setMin(yBottom);
            m_savedY->setTitleText("Saved " + data->getUnit());

        }


    }

    //m_eleSeries->replace(data->getData());

    m_data[data->getCategory()] = data;



//    delete data;
}

void Model::updateProductionPieModel(DataContainer *currentData)
{
    int index = 0;
    m_pieseries->clear();
    for(QPointF point : currentData->getData())
    {
        qDebug() << "Piemodel() x: " << point.rx() << " y: " << point.ry() << " type: " << currentData->getType() << " category: " << currentData->getCategory();
        switch (index) {
        case 0:
            m_pieseries->append("Hydro", point.ry());
            m_hydroConsumption = QString("%1 MWh/h").arg(point.ry());
            break;
        case 1:
            m_pieseries->append("Wind", point.ry());
            m_windConsumption = QString("%1 MWh/h").arg(point.ry());
            break;
        case 2:
            m_pieseries->append("Nuclear", point.ry());
            m_nucklearConsumption = QString("%1 MWh/h").arg(point.ry());
            break;

        }
        ++index;
    }
    qDebug() << "hyd " << m_hydroConsumption << " wind " << m_windConsumption << " nuck " << m_nucklearConsumption;
    m_pieseries->setLabelsVisible(true);
    emit pieSeriesChanged();
}


