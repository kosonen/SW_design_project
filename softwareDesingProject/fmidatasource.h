#ifndef FMIAPI_H
#define FMIAPI_H

#include "idatasource.h"

class FmiDataSource : public IDataSource
{
    Q_OBJECT
public:

    FmiDataSource(QObject* parent = nullptr);
    virtual ~FmiDataSource();

    virtual void load(QUrl url) override;

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:
    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;

};

#endif // FMIAPI_H
