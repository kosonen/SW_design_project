#ifndef API_H
#define API_H

#include "datacontainer.h"

#include <QObject>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include <QNetworkReply>
#include <QDomDocument>


class IDataSource : public QObject
{
    Q_OBJECT
public:
    explicit IDataSource(QObject *parent = nullptr) : QObject(parent) {};
    virtual void load(QUrl url) = 0;

signals:
    void dataParsed(DataContainer* data);
};

#endif // API_H
