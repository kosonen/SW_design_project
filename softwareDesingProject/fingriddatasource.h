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

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QUrl buildFingridURL();


    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QHash<QString,QString> queryParameters_;

    QString source_;
    QDateTime startTime_;
    QDateTime endTime_;

};

#endif // FINGRIDAPI_H
