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

    void load(QUrl url);
    QList<QPointF> getData();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QList<QPointF> data_;

};

#endif // FINGRIDAPI_H
