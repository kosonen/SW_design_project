#ifndef FMIAPI_H
#define FMIAPI_H

#include "idatasource.h"
#include "defines.h"

/**
 * @brief The FmiDataSource class implements fetching from the FMI API
 */
class FmiDataSource : public IDataSource
{
    Q_OBJECT
public:

    FmiDataSource(QObject* parent = nullptr);
    virtual ~FmiDataSource();

    /**
     * @brief setTimeWindow, for setting the time window for the next fetch
     * @param startTime, start time of the fetch, in ISO format
     * @param endTime, end time of the fetch, in ISO format
     */
    virtual void setTimeWindow(const QString startTime, const QString endTime);

    /**
     * @brief makeRequest, makes the actual request to the network API, emits
     * dataParsed signal when data is ready.
     */
    virtual void makeRequest();

    /**
     * @brief setSearchParameter, sets the search parameter for the next fetch
     * @param param, the parameter for the next search, for example "temperature
     * for FMI API
     */
    virtual void setSearchParameter(const QString param);

    /**
     * @brief setLocation, sets the location for the next fetch
     * @param location, location for the next fetch, for example "Viitasaari"
     */
    virtual void setLocation(const QString location);


private Q_SLOTS:

    /**
     * @brief Emitted when request is completed
     * @param reply
     */
    void downloadCompleted(QNetworkReply* reply);

private:
    QUrl buildFMIURL(bool forecast, QString startTime, QString endTime);
    void fetchHandler();

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QList<QPointF> dataBuffer_;

    bool firstFetchHandled_;

    /* Handle these separately from other parameters */
    QDateTime startTime_;
    QDateTime endTime_;
    QString source_;
    QString location_;

};

#endif // FMIAPI_H
