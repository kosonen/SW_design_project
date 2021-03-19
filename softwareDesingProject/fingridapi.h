#ifndef FINGRIDAPI_H
#define FINGRIDAPI_H

#include "api.h"
#include "defines.h"

class FingridAPI : public API
{
    Q_OBJECT
public:
    explicit FingridAPI(QObject* parent = nullptr);
    ~FingridAPI();

    void load(const QString &url);
    QList<QPointF> getData();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QList<QPointF> data_;

};

#endif // FINGRIDAPI_H
