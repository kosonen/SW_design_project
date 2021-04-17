#ifndef FINGRIDAPI_H
#define FINGRIDAPI_H

#include "idatasource.h"
#include "defines.h"

class FingridDataSource : public IDataSource
{
    Q_OBJECT
public:
    explicit FingridDataSource(QObject* parent = nullptr);
    ~FingridDataSource();

    virtual void setTimeWindow(QString startTime, QString endTime);
    virtual void makeRequest();
    virtual void setSearchParameter(const QString param);
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
