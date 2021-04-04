#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_urlBuilder(nullptr),
    m_requestFMIAPI(),
    m_tempSeries{},
    m_humSeries{},
    m_eleProductionSeries{},
    m_eleConsumptionSeries{},
    m_windProductionSeries{},
    m_nuclearProductionSeries{},
    m_hydroProductionSeries{},
    m_weatherY{},
    m_enegyY{},
    m_start(),
    m_end()

{
    m_urlBuilder = URLBuilder::getInstance();
    connect(&m_requestFMIAPI, &FMIAPI::dataParsed, this, &Model::updateTemp);
}

QtCharts::QLineSeries *Model::getTempSeries() const
{
    return m_tempSeries;
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

QPointF Model::getLimits(QList<QPointF> data)
{
    qreal top = 0;
    qreal bottom = 0;
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



void Model::setTempSeries(QtCharts::QLineSeries *tempSeries)
{
    m_tempSeries = tempSeries;
    emit tempSeriesChanged();
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


bool Model::update(DataRequestSettings settings)
{
    qDebug() << "Updating model";
    bool isOk = false;
    for(QString source : settings.getDatasources())
    {
        qDebug() << "SOURCE IS: " << source << Qt::endl;
        if(SOURCE_TO_API_MAPPING.contains(source))
        {
            QUrl url;
            if(SOURCE_TO_API_MAPPING[source] == "FMI")
            {
                isOk = m_urlBuilder->buildFMIURL(settings, url, source);
                if(!isOk)
                {
                    qDebug() << "Failed to build FMI url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << url.toString();
                m_requestFMIAPI.load(url);

            }
            else if(SOURCE_TO_API_MAPPING[source] == "FINGRID")
            {
                isOk = m_urlBuilder->buildFingridURL(settings, url, source);
                if(!isOk)
                {
                    qDebug() << "Failed to build Fingrid url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << url.toString();
                //m_requestFingridAPI.load(url);
            }
        }
        else
        {
            qDebug()<< "Unknown option";
            return isOk;
        }
    }
    isOk = true;
    return isOk;
}



void Model::updateTemp()
{
    qDebug() << "Updating temperature graph" << Qt::endl;

    QList<QPointF> data = m_requestFMIAPI.getData();

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

    m_tempSeries->replace(data);

    // update Y axis limits
    QPointF limits = getLimits(data);
    qreal yTop = limits.x() + 1;
    qreal yBottom = limits.y() - 1;
    setWeatherY(QPointF(yTop, yBottom));

}


