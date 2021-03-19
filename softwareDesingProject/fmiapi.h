#ifndef FMIAPI_H
#define FMIAPI_H

#include "api.h"

class FMIAPI : public API
{
    Q_OBJECT
public:

     FMIAPI(QObject* parent = nullptr);
     virtual ~FMIAPI();

    void load(const QString &url);
    QVector<QPair<QString, QString>> getData();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QVector<QPair<QString, QString>> data_;

};

#endif // FMIAPI_H
