#ifndef FMIAPI_H
#define FMIAPI_H

#include "idatasource.h"

class FmiDataSource : public IDataSource
{
    Q_OBJECT
public:

     FmiDataSource(QObject* parent = nullptr);
     virtual ~FmiDataSource();

    void load(QUrl url);
    QList<QPointF> getData();

signals:
    void dataParsed();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QList<QPointF> data_;

};

#endif // FMIAPI_H
