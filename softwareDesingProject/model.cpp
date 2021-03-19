#include "model.h"
#include "defines.h"

Model::Model(QObject *parent):
    QObject(parent),
    m_urlBuilder(nullptr),
    m_requestFMIAPI()
{
    m_urlBuilder = URLBuilder::getInstance();
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
