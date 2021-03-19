#ifndef API_H
#define API_H

#include <QObject>
#include <QVector>
#include <QPair>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include <QNetworkReply>
#include <QDomDocument>


class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = nullptr) : QObject(parent) {};
    virtual void load(const QString &url) = 0;
    virtual QVector<QPair<QString, QString>> getData() = 0;
};

#endif // API_H
