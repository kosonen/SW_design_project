#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_dataFetcher(new DataFetcher),
    m_weatherSeries{},
    m_weatherType("temperature"),
    m_eleProductionSeries{},
    m_eleConsumptionSeries{},
    m_windProductionSeries{},
    m_nuclearProductionSeries{},
    m_hydroProductionSeries{},
    m_weatherY{},
    m_enegyY{},
    m_start(),
    m_end(),
    m_chart(nullptr)
{
    connect(m_dataFetcher, &DataFetcher::dataReady, this, &Model::updateTemp);
}

QtCharts::QLineSeries *Model::getWeatherSeries() const
{
    return m_weatherSeries;
}

QtCharts::QChart* Model::getChartView() const
{
    return m_chart;
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

QString Model::getWeatherType()
{
    return m_weatherType;
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
    qDebug() << "Setting line" << Qt::endl;
    qDebug() << "Setting line" << Qt::endl;
    qDebug() << "Setting line" << Qt::endl;
    qDebug() << "Setting line" << Qt::endl;

    qDebug() << "Series: " << weatherSeries << Qt::endl;

    m_weatherSeries = weatherSeries;
    m_chart = weatherSeries->chart();
    emit weatherSeriesChanged();
}

void Model::setChartView(QtCharts::QChart* chart)
{
    qDebug() << "Setting chart" << Qt::endl;
    qDebug() << "Setting chart" << Qt::endl;
    qDebug() << "Setting chart" << Qt::endl;
    qDebug() << "Setting chart" << Qt::endl;

    qDebug() << "Series: " << chart << Qt::endl;

//    m_chart = dynamic_cast<QtCharts::QChart*>(chart);
    emit chartViewChanged();
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

void Model::setWeatherType(QString newType)
{
    m_weatherType = newType;
    emit weatherTypeChanged();
}


bool Model::update(DataRequestSettings settings)
{
    return m_dataFetcher->fetch(settings);
}

void Model::updateTemp(QList<QPointF> data)
{
    qDebug() << "Updating temperature graph" << Qt::endl;
    qDebug() << "Chart address: " << m_chart << Qt::endl;
    qDebug() << "series address: " << m_weatherSeries << Qt::endl;
    if (m_chart != nullptr)
    {
        qDebug() << "Series count: " << m_chart->series().size() << Qt::endl;
    }

    qDebug() << data.size() << Qt::endl;
    if (data.size() < 2)
    {
        qDebug() << "tyhjä" << Qt::endl;
        return;
    }

    for (auto p : data)
    {
        qDebug() << "X: " << p.x() << "Y: " << p.y() << Qt::endl;
    }

    setStartTime(QDateTime::fromMSecsSinceEpoch(data.first().rx()));
    setEndTime(QDateTime::fromMSecsSinceEpoch(data.last().rx()));

    m_weatherSeries->replace(data);

    // update Y axis limits
    QPointF limits = getLimits(data);
    qreal yTop = limits.x() + 1;
    qreal yBottom = limits.y() - 1;
    setWeatherY(QPointF(yTop, yBottom));

}


