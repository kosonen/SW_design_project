#ifndef FINGRIDAPI_H
#define FINGRIDAPI_H

#include "idatasource.h"
#include "defines.h"

/**
 * @brief The FingridDataSource class implements fetching from the Fingrid API
 */
class FingridDataSource : public IDataSource
{
    Q_OBJECT
public:
    explicit FingridDataSource(QObject* parent = nullptr);
    ~FingridDataSource();

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
     * @brief getCurrentProduction, fetches data of the current different production
     * forms for the pie model. Emits currentProductionReady signal when ready
     */
    void getCurrentProduction();

signals:
    void currentProductionReady(DataContainer* data);

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);
    void pieModelDownloadCompleted(QNetworkReply* reply);

private:

    QUrl buildFingridURL(bool forecast, QString startTime, QString endTime);
    QUrl buildFingridURL(QString source);
    void parseData(QDomDocument& doc, QList<QPointF>& buffer);
    void parsePieModelData(QDomDocument& doc, QList<QPointF>& buffer);
    void pieModelFetchHandler();
    void fetchHandler();



    QNetworkAccessManager* network_;
    QNetworkAccessManager* pieModelNetwork_;

    QString source_;
    QDateTime startTime_;
    QDateTime endTime_;

    QList<QPointF> dataBuffer_;
    bool previousFetchesHandled_;

    bool fetchingPieModel_;
    int numberOfFetches_;
    QList<QPointF> pieModelDataBuffer_;


};

#endif // FINGRIDAPI_H
