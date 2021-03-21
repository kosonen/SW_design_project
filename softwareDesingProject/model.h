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
#include <QDateTime>

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* tempSeries READ getTempSeries WRITE setTempSeries NOTIFY tempSeriesChanged)
    Q_PROPERTY(QDateTime startTime READ getStartTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ getEndTime WRITE setEndTime NOTIFY endTimeChanged)


public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    QtCharts::QLineSeries* getTempSeries() const;
    QDateTime getStartTime();
    QDateTime getEndTime();


    void setTempSeries(QtCharts::QLineSeries *tempSeries);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);

    bool update(DataRequestSettings settings);

    // populate series with random crap
    // for testing/debug only
    Q_INVOKABLE void populateTempSeries();
    Q_INVOKABLE void initTimeAxis();

    Q_INVOKABLE void updateTemp();

signals:

    void tempSeriesChanged();
    void startTimeChanged();
    void endTimeChanged();

private:
    IURLBuilder* m_urlBuilder;
    FMIAPI m_requestFMIAPI;
    FingridAPI m_requestFingridAPI;
    QtCharts::QLineSeries* m_tempSeries;
    QDateTime m_start;
    QDateTime m_end;


};

#endif // MODEL_H
