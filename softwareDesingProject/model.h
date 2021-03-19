#ifndef MODEL_H
#define MODEL_H

#include "datarequestsettings.h"
#include "iurlbuilder.h"
#include "urlbuilder.h"
#include "api.h"
#include "fmiapi.h"
#include "fingridapi.h"

#include <QObject>
#include <QChart>
#include <QLineSeries>

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* tempSeries READ getTempSeries WRITE setTempSeries NOTIFY tempSeriesSignal)

public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    QtCharts::QLineSeries* getTempSeries() const;

    void setTempSeries(QtCharts::QLineSeries *tempSeries);

    bool update(DataRequestSettings settings);

    // populate series with random crap
    // for testing/debug only
    Q_INVOKABLE void populateTempSeries();

signals:

    void tempSeriesSignal();

private:
    IURLBuilder* m_urlBuilder;
    FMIAPI m_requestFMIAPI;
    FingridAPI m_requestFingridAPI;
    QtCharts::QLineSeries* m_tempSeries ;

};

#endif // MODEL_H
