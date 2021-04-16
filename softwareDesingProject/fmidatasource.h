#ifndef FMIAPI_H
#define FMIAPI_H

#include "idatasource.h"
#include "defines.h"

class FmiDataSource : public IDataSource
{
    Q_OBJECT
public:

    FmiDataSource(QObject* parent = nullptr);
    virtual ~FmiDataSource();

    virtual void setLocation(QString location);
    virtual void setTimeWindow(QString startTime, QString endTime);
    virtual void makeRequest();
    virtual void setSearchParameter(const QString param);


private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:
    QUrl buildFMIURL(bool forecast, QString startTime, QString endTime);
    void fetchHandler();

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QHash<QString,QString> queryParameters_;
    QList<QPointF> dataBuffer_;

    bool firstFetchHandled_;

    /* Handle these separately from other parameters */
    QDateTime startTime_;
    QDateTime endTime_;
    QString source_;
    QString location_;

};

#endif // FMIAPI_H
