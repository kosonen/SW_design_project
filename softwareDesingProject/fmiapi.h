#ifndef FMIAPI_H
#define FMIAPI_H

#include "api.h"

class FMIAPI : public API
{
    Q_OBJECT
public:

     FMIAPI(QObject* parent = nullptr);
     virtual ~FMIAPI();

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
