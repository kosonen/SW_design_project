#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include "datacontainer.h"
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
    void dataReady(DataContainer* data);

private:
    IURLBuilder* m_urlBuilder;
    FmiDataSource* m_requestFMIAPI;
    FingridDataSource* m_requestFingridAPI;

};

#endif // DATAFETCHER_H
