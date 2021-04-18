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

/**
 * @brief The DataFetcher class controls the different network APIs, mapping the
 * requests to the correct API and forwarding processed data forward
 */


class DataFetcher : public QObject
{
    Q_OBJECT
public:
    explicit DataFetcher(QObject *parent = nullptr);

    /**
     * @brief fetch, handles the fetching from the correct API based on the settings
     * passed to it
     * @param settings, current fetch settings
     * @return
     * True,  if fetching from API was successful
     * False, if fetching from the API failed
     */
    bool fetch(Settings& settings);
    /**
     * @brief setDataProcessingMethod, sets the method for processing the fetched
     * data. Can calculate daily avg, min and max
     * @param method, method for processing the data
     * AVG = daily average
     * MIN = daily min
     * MAX = daily max
     * others = returns unprocessed data
     */
    void setDataProcessingMethod(const QString method);

signals:

    /**
     * @brief Emitted when data is ready
     * @param data
     */
    void dataReady(DataContainer* data);

    /**
     * @brief Emitted when current production data is ready
     * @param currentData
     */
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
