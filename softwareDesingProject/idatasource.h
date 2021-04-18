#ifndef API_H
#define API_H

#include "datacontainer.h"

#include <QObject>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include <QNetworkReply>
#include <QDomDocument>
#include <QHash>
#include <memory>

/**
 * @brief The IDataSource class is an interface class for network APIs
 */


class IDataSource : public QObject
{
    Q_OBJECT
public:
    explicit IDataSource(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief setTimeWindow, for setting the time window for the next fetch
     * @param startTime, start time of the fetch, in ISO format
     * @param endTime, end time of the fetch, in ISO format
     */
    virtual void setTimeWindow(const QString startTime, const QString endTime) = 0;

    /**
     * @brief makeRequest, makes the actual request to the network API, emits
     * dataParsed signal when data is ready.
     */

    virtual void makeRequest() = 0;

    /**
     * @brief setSearchParameter, sets the search parameter for the next fetch
     * @param param, the parameter for the next search, for example "temperature
     * for FMI API
     */
    virtual void setSearchParameter(const QString param) = 0;

signals:
    void dataParsed(DataContainer* data);
};

#endif // API_H
