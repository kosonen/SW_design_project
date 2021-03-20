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

void Model::populateTempSeries()
{
    m_tempSeries->append(-4,-6);
    m_tempSeries->append(0,0);
    m_tempSeries->append(1,2);
    m_tempSeries->append(3,4);
    m_tempSeries->append(1727159758,1);

}

void Model::initTimeAxis()
{
    setStartTime(QDateTime::fromMSecsSinceEpoch(1616181405365));
    setEndTime(QDateTime::fromMSecsSinceEpoch(1616183405365));
}


