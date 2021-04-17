#include "datafetcher.h"

DataFetcher::DataFetcher(QObject *parent):
    QObject(parent),
    m_requestFMIAPI(new FmiDataSource),
    m_requestFingridAPI(new FingridDataSource)
{
    connect(m_requestFMIAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataReady);
    connect(m_requestFingridAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataReady);
}

bool DataFetcher::fetch(DataRequestSettings& settings)
{
    qDebug() << "Updating model";

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
