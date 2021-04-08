#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include "datarequestsettings.h"
#include "iurlbuilder.h"
#include "urlbuilder.h"
#include "idatasource.h"
#include "fmidatasource.h"
#include "fingriddatasource.h"


#include <QObject>

class DataFetcher : public QObject
{
    Q_OBJECT
public:
    explicit DataFetcher(QObject *parent = nullptr);

    bool fetch(DataRequestSettings settings);

signals:
    void dataReady(QList<QPointF> data);

private:
    IURLBuilder* m_urlBuilder;
    FmiDataSource* m_requestFMIAPI;
    FingridDataSource* m_requestFingridAPI;

};

#endif // DATAFETCHER_H
