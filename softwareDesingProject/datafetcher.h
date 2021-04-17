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
    void setDataProcessingMethod(QString method);

signals:
    void dataReady(DataContainer* data);
    void currentProductionReady(DataContainer* currentData);
private:
    void dataProcessingHandler(DataContainer* data);

    DataContainer* calcAverage(DataContainer* data);
    DataContainer* calcMin(DataContainer* data);
    DataContainer* calcMax(DataContainer* data);

    FmiDataSource* m_requestFMIAPI;
    FingridDataSource* m_requestFingridAPI;
    QString m_dataProcessingMethod_;

};

#endif // DATAFETCHER_H
