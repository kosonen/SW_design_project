#include "datafetcher.h"

DataFetcher::DataFetcher(QObject *parent):
    QObject(parent),
    m_requestFMIAPI(new FmiDataSource),
    m_requestFingridAPI(new FingridDataSource),
    m_dataProcessingMethod_("NONE")
{
    connect(m_requestFMIAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataProcessingHandler);
    connect(m_requestFingridAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataProcessingHandler);
    connect(m_requestFingridAPI, &FingridDataSource::currentProductionReady, this, &DataFetcher::currentProductionReady);
}

bool DataFetcher::fetch(Settings& settings)
{
    qDebug() << "Updating model";

    m_requestFingridAPI->getCurrentProduction();

    QUrl url;
    IDataSource* dataSource = nullptr;

    for (QString source : settings.getDatasources())
    {
        if (!SOURCE_TO_API_MAPPING.contains(source))
        {
            qDebug() << "Error: Unknown option";
            return false;
        }

        // TODO: There needs to be better solution for selecting between the
        // dataSources. Also the urlBuilder needs some adjustment.
        if (SOURCE_TO_API_MAPPING[source] == "FMI")
        {
            qDebug() << "FMI REQUEST";
            m_requestFMIAPI->setLocation(settings.getLocation());
            dataSource = dynamic_cast<IDataSource*>(m_requestFMIAPI);
        }
        else if (SOURCE_TO_API_MAPPING[source] == "FINGRID")
        {
            dataSource = dynamic_cast<IDataSource*>(m_requestFingridAPI);
        }

        // Make data request
        dataSource->setTimeWindow(settings.getStartTime(), settings.getEndTime());
        dataSource->setSearchParameter(source);
        dataSource->makeRequest();

    }

    return true;
}

void DataFetcher::setDataProcessingMethod(QString method)
{
    m_dataProcessingMethod_ = method;
}

void DataFetcher::dataProcessingHandler(DataContainer* data)
{
    qDebug() << data->size();
    DataContainer* processedData = data;
    if(m_dataProcessingMethod_== "AVG")
        processedData = calcAverage(data);
    else if(m_dataProcessingMethod_== "MAX")
        processedData = calcMax(data);
    else if(m_dataProcessingMethod_== "MIN")
        processedData = calcMin(data);
    else
        processedData = data;
    emit dataReady(processedData);

}

DataContainer* DataFetcher::calcAverage(DataContainer* data)
{
    qDebug() << "PROCESSING AVG";
    if(data->size() > 0){
        QDate date = QDateTime::fromMSecsSinceEpoch(data->getElement(0).x()).date();
        double avg = 0.0;
        unsigned int iterations = 0;
        DataContainer* avgData = new DataContainer;
        for(int i = 0; i < data->size(); i++)
        {
            QPointF it = data->getElement(i);
            iterations++;
            QDateTime currDateTime = QDateTime::fromMSecsSinceEpoch(it.x());
            //qDebug() << date << currDateTime;
            if(currDateTime.date() != date){
                avg = avg/iterations;
                avgData->addElement(QPointF(date.startOfDay().toMSecsSinceEpoch(), avg));
                date = currDateTime.date();
                avg = 0;
                iterations = 0;
            }
            avg += it.y();
        }
        delete data;
        return avgData;
    }
    else
    {
        return data;
    }
}

DataContainer* DataFetcher::calcMin(DataContainer* data)
{
    if(data->size() > 0){
        QDate date = QDateTime::fromMSecsSinceEpoch(data->getElement(0).x()).date();
        double min = data->getElement(0).y();
        DataContainer* minData = new DataContainer;
        for(int i = 0; i < data->size(); i++)
        {
            QPointF it = data->getElement(i);
            QDateTime currDateTime = QDateTime::fromMSecsSinceEpoch(it.x());
            if(currDateTime.date() != date){

                minData->addElement(QPointF(date.startOfDay().toMSecsSinceEpoch(), min));
                date = currDateTime.date();
                min = it.y();
            }
            if(it.y() < min)
            {
                min = it.y();
            }
        }
        delete data;
        return minData;
    }
    else
    {
        return data;
    }
}

DataContainer* DataFetcher::calcMax(DataContainer* data)
{

    if(data->size() > 0){
        QDate date = QDateTime::fromMSecsSinceEpoch(data->getElement(0).x()).date();
        double max = data->getElement(0).y();
        DataContainer* maxData = new DataContainer;
        for(int i = 0; i < data->size(); i++)
        {
            QPointF it = data->getElement(i);
            QDateTime currDateTime = QDateTime::fromMSecsSinceEpoch(it.x());
            if(currDateTime.date() != date){
                maxData->addElement(QPointF(date.startOfDay().toMSecsSinceEpoch(), max));
                date = currDateTime.date();
                max = it.y();
            }
            if(it.y() > max)
            {
                max = it.y();
            }
        }
        delete data;
        return maxData;
    }
    else
    {
        return data;
    }
}


