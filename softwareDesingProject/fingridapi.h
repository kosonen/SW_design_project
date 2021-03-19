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
    QVector<QPair<QString, QString>> getData();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network_;
    QXmlStreamReader* parser_;
    QVector<QPair<QString, QString>> data_;

};

#endif // FINGRIDAPI_H
