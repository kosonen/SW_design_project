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
    Q_PROPERTY(QPointF weatherY READ getWeatherY WRITE setWeatherY NOTIFY weatherYChanged)


public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    QtCharts::QLineSeries* getTempSeries() const;
    QDateTime getStartTime();
    QDateTime getEndTime();
    QPointF getWeatherY();

    QPointF getLimits(QList<QPointF> data);


    void setTempSeries(QtCharts::QLineSeries *tempSeries);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);
    void setWeatherY(QPointF newValue);

    bool update(DataRequestSettings settings);


public slots:
    void updateTemp();

signals:

    void tempSeriesChanged();
    void startTimeChanged();
    void endTimeChanged();
    void weatherYChanged();

private:
    IURLBuilder* m_urlBuilder;
    FMIAPI m_requestFMIAPI;
    FingridAPI m_requestFingridAPI;
    QtCharts::QLineSeries* m_tempSeries;
    QtCharts::QLineSeries* m_humSeries;
    QtCharts::QLineSeries* m_eleProductionSeries;
    QtCharts::QLineSeries* m_eleConsumptionSeries;
    QtCharts::QLineSeries* m_windProductionSeries;
    QtCharts::QLineSeries* m_nuclearProductionSeries;
    QtCharts::QLineSeries* m_hydroProductionSeries;
    QPointF m_weatherY;
    QPointF m_enegyY;
    QDateTime m_start;
    QDateTime m_end;


};

#endif // MODEL_H
