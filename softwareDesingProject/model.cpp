#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_dataFetcher(new DataFetcher),
    m_weatherSeries{},
    m_eleSeries{},
    m_savedSeries{},
    m_weatherType("Temperature"),
    m_electricityType("Hydro power"),
    /*
    m_eleProductionSeries{},
    m_eleConsumptionSeries{},
    m_windProductionSeries{},
    m_nuclearProductionSeries{},
    m_hydroProductionSeries{},
    */
    m_weatherY{new QtCharts::QValueAxis},
    m_elelctricityY{new QtCharts::QValueAxis},
    m_savedY{new QtCharts::QValueAxis},
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


bool Model::update(Settings& settings)
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


    if(data->getCategory() == "weather")
    {
        m_weatherSeries->replace(data->getData());

        switch(LINE_SERIES_MAPPING[m_weatherType]){
            case 1:
                m_weatherSeries->setColor("red");
                m_weatherSeries->setName("Temperature");
                m_weatherY->setTitleText("°C");
                break;
            case 2:
                m_weatherSeries->setColor("cyan");
                m_weatherSeries->setName("Wind speed");
                m_weatherY->setTitleText("M/S");
                break;
            case 3:
                m_weatherSeries->setColor("blue");
                m_weatherSeries->setName("Humidity");
                m_weatherY->setTitleText("%");
                break;
            case 4:
                m_weatherSeries->setColor("gray");
                m_weatherSeries->setName("Cloud Cover");
                m_weatherY->setTitleText("/ 8");
                break;
        }

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

        switch(LINE_SERIES_MAPPING[m_electricityType]){
            case 5:
                m_eleSeries->setColor("darkblue");
                m_eleSeries->setName("Hydro power");
                m_elelctricityY->setTitleText(data->getUnit());
                break;
            case 6:
                m_eleSeries->setColor("darkgreen");
                m_eleSeries->setName("Wind power");
                qDebug() << data->getUnit() << Qt::endl;
                m_elelctricityY->setTitleText(data->getUnit());
                break;
            case 7:
                m_eleSeries->setColor("darkcyan");
                m_eleSeries->setName("Nuclear power");
                m_elelctricityY->setTitleText(data->getUnit());
                break;
            case 8:
                m_eleSeries->setColor("lightgreen");
                m_eleSeries->setName("Energy consumption");
                break;
            case 9:
                m_eleSeries->setColor("lightblue");
                m_eleSeries->setName("Energy production");
        }

        QPointF limits = getLimits(data->getData());
        qreal yTop = limits.x() + 10;
        qreal yBottom = 0;

        m_elelctricityY->setMax(yTop);
        m_elelctricityY->setMin(yBottom);

    }

    else if (data->getCategory() == "save")
    {
        m_savedSeries->replace(data->getData());

        qDebug() << "data type: " << data->getType() << Qt::endl;
        if(data->getType() == "temperature" || data->getType() == "windspeedms"
                || data->getType() == "humidity" || data->getType() == "TotalCouldCover"){

            m_savedSeries->setName("Saved " + WEATHER_OPTION_TO_MODEL_MAPPING[data->getType()]);
            qDebug() << "Hashed value: " << WEATHER_OPTION_TO_MODEL_MAPPING[data->getType()] << Qt::endl;

            QPointF limits = getLimits(data->getData());
            qreal yTop = limits.x() + 1;
            qreal yBottom = 0;

            if(data->getType() == "temperature")
            {
                yBottom = limits.y() - 1;
            }
            m_savedY->setMax(yTop);
            qDebug() << "Y top: " << yTop << Qt::endl;
            m_savedY->setMin(yBottom);
            m_savedY->setTitleText("Saved " + data->getUnit());

        }
        else {

            m_savedSeries->setName("Saved " + data->getType());

            QPointF limits = getLimits(data->getData());
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


