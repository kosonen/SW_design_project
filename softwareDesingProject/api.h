#ifndef API_H
#define API_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QList>
#include <QPointF>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include <QNetworkReply>
#include <QDomDocument>


class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = nullptr) : QObject(parent) {};
    virtual void load(QUrl url) = 0;
    virtual QList<QPointF> getData() = 0;
};

#endif // API_H
