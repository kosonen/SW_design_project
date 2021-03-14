#ifndef API_H
#define API_H

#include <QObject>
#include <QVector>
#include <QPair>

#include <QNetworkAccessManager>
#include <QXmlStreamReader>

class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = nullptr);

    void load(const QString &url);
    QVector<QPair<QString, QString>> getData();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* reply);

private:

    QNetworkAccessManager* network;
    QXmlStreamReader* parser;
    QVector<QPair<QString, QString>> data;
};

#endif // API_H
