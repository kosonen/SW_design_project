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

QString Model::getHydroProduction()
{
    return m_hydroConsumption;
}

QString Model::getNuclearProduction()
{
    return m_nucklearConsumption;
}

QString Model::getWindProduction()
{
    return m_windConsumption;
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
    if (data->getData().size() < 1)
    {
        qDebug() << "empty" <<  Qt::endl;
        emit emptySeries();
        return;
    }

    QtCharts::QLineSeries* series = nullptr;
    QtCharts::QValueAxis* axis = nullptr;

    // Select series
    if(data->getCategory() == "weather")
    {
        series = m_weatherSeries;
        axis = m_weatherY;
    }
    else if (data->getCategory() == "electricity")
    {
        series = m_eleSeries;
        axis = m_elelctricityY;
    }
    else if (data->getCategory() == "save")
    {
        series = m_savedSeries;
        axis = m_savedY;
    }

    series->replace(data->getData());
    if (data->getCategory() == "save")
    {
        series->setName("Saved " + SOURCE_TO_NAME_MAPPING[data->getType()]);
    }
    else
    {
        series->setName(SOURCE_TO_NAME_MAPPING[data->getType()]);
        series->setColor(SOURCE_TO_COLOR_MAPPING[data->getType()]);
    }

    QPointF limits = data->getLimits();
    qreal yTop = limits.x() > 0 ? limits.x() * 1.1 : limits.x() * 0.9;
    qreal yBottom = limits.y() > 0 ? limits.y() * 0.9 : limits.y() * 1.1;

    axis->setMax(yTop);
    axis->setMin(yBottom);
    axis->setTitleText(data->getUnit());

    // Deallocate DataContainer
    if(m_data.count(data->getCategory()))
    {
        delete m_data[data->getCategory()];
        m_data[data->getCategory()] = nullptr;
    }

    m_data[data->getCategory()] = data;
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


