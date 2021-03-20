#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_urlBuilder(nullptr),
    m_requestFMIAPI(),
    m_tempSeries{},
    m_start(),
    m_end()

{
    m_urlBuilder = URLBuilder::getInstance();
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


bool Model::update(DataRequestSettings settings)
{
    qDebug() << "Updating model";
    bool isOk = false;
    for(QString source : settings.getDatasources())
    {
        if(SOURCE_TO_API_MAPPING.contains(source))
        {
            QString urlString = QString();
            if(SOURCE_TO_API_MAPPING[source] == "FMI")
            {
                isOk = m_urlBuilder->buildFMIURL(settings, urlString);
                if(!isOk)
                {
                    qDebug() << "Failed to build FMI url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << urlString;
                m_requestFMIAPI.load(urlString);

            }
            else if(SOURCE_TO_API_MAPPING[source] == "FINGRID")
            {
                isOk = m_urlBuilder->buildFingridURL(settings, urlString);
                if(!isOk)
                {
                    qDebug() << "Failed to build Fingrid url";
                    return isOk;
                }
                qDebug() << "Requestind data with url " << urlString;
                m_requestFMIAPI.load(urlString);
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

void Model::populateTempSeries()
{
    m_tempSeries->append(m_start.toMSecsSinceEpoch(),-6);
    m_tempSeries->append((m_start.toMSecsSinceEpoch()+m_end.toMSecsSinceEpoch())/2, 6);
    m_tempSeries->append(m_end.toMSecsSinceEpoch(),2);

}

void Model::initTimeAxis()
{
    setStartTime(QDateTime::fromMSecsSinceEpoch(1616181405365));
    setEndTime(QDateTime::fromMSecsSinceEpoch(1616183305365));
}


