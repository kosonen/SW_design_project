#include "datafetcher.h"

DataFetcher::DataFetcher(QObject *parent):
    QObject(parent),
    m_urlBuilder(nullptr),
    m_requestFMIAPI(new FmiDataSource),
    m_requestFingridAPI(new FingridDataSource)
{
    m_urlBuilder = URLBuilder::getInstance();
    connect(m_requestFMIAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataReady);
    connect(m_requestFingridAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataReady);
}

bool DataFetcher::fetch(DataRequestSettings settings)
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
            if (!m_urlBuilder->buildFMIURL(settings, url, source))
            {
                qDebug() << "Failed to build FMI url";
                return false;
            }
            dataSource = dynamic_cast<IDataSource*>(m_requestFMIAPI);
        }
        else if (SOURCE_TO_API_MAPPING[source] == "FINGRID")
        {
            if (!m_urlBuilder->buildFingridURL(settings, url, source))
            {
                qDebug() << "Failed to build Fingrid url";
                return false;
            }
            qDebug() << "url " << url.toString();
            dataSource = dynamic_cast<IDataSource*>(m_requestFingridAPI);
        }

        // Make data request
        dataSource->load(url);
    }

    return true;
}
