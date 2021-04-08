#include "datafetcher.h"

DataFetcher::DataFetcher(QObject *parent):
    QObject(parent),
    m_urlBuilder(nullptr),
    m_requestFMIAPI()
{
    m_urlBuilder = URLBuilder::getInstance();
    connect(&m_requestFMIAPI, &FmiDataSource::dataParsed, this, &DataFetcher::dataReady);
}

bool DataFetcher::fetch(DataRequestSettings settings)
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
