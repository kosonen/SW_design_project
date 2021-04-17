#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include "datacontainer.h"
#include "settings.h"
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

    bool fetch(Settings& settings);

signals:
    void dataReady(DataContainer* data);

private:
    FmiDataSource* m_requestFMIAPI;
    FingridDataSource* m_requestFingridAPI;

};

#endif // DATAFETCHER_H
