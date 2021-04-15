#ifndef API_H
#define API_H

#include "datacontainer.h"

#include <QObject>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include <QNetworkReply>
#include <QDomDocument>
#include <QHash>


class IDataSource : public QObject
{
    Q_OBJECT
public:
    explicit IDataSource(QObject *parent = nullptr) : QObject(parent) {}

    virtual void setTimeWindow(QString startTime, QString endTime) = 0;
    virtual void makeRequest() = 0;
    virtual void setSearchParameter(const QString param) = 0;

    // Sitten vielä mahdollisesti jotain metodeja tuon piirakkamallin
    // toteutukseen.

signals:
    void dataParsed(DataContainer* data);
};

#endif // API_H
