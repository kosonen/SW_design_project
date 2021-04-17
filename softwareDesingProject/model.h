#ifndef MODEL_H
#define MODEL_H

#include "datacontainer.h"
#include "datarequestsettings.h"
#include "datafetcher.h"

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QDateTime>

//enum weatherT {temperature, wind, humidity, NONE};

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* weatherSeries READ getWeatherSeries WRITE setWeatherSeries NOTIFY weatherSeriesChanged)
    Q_PROPERTY(QtCharts::QLineSeries* elecrtricitySeries READ getElectricitySeries WRITE setElectricitySeries NOTIFY electricitySeriesChanged)
    Q_PROPERTY(QDateTime startTime READ getStartTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ getEndTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QPointF weatherY READ getWeatherY WRITE setWeatherY NOTIFY weatherYChanged)
    Q_PROPERTY(QPointF electricityY READ getElectricityY WRITE setElectricityY NOTIFY electricityYChanged)
    Q_PROPERTY(QString weatherType READ getWeatherType WRITE setWeatherType NOTIFY weatherTypeChanged)


public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    QtCharts::QLineSeries* getWeatherSeries() const;
    QtCharts::QLineSeries* getElectricitySeries() const;
    QDateTime getStartTime();
    QDateTime getEndTime();
    QPointF getWeatherY();
    QPointF getElectricityY();
    QString getWeatherType();

    QPointF getLimits(QList<QPointF> data);


    void setWeatherSeries(QtCharts::QLineSeries *weatherSeries);
    void setElectricitySeries(QtCharts::QLineSeries *electricitySeries);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);
    void setWeatherY(QPointF newValue);
    void setElectricityY(QPointF newValue);
    void setWeatherType(QString newType);

    bool update(DataRequestSettings& settings);


public slots:
    void updateSeries(DataContainer* data);

signals:

    void weatherSeriesChanged();
    void startTimeChanged();
    void endTimeChanged();
    void weatherYChanged();
    void electricityYChanged();
    void weatherTypeChanged();
    void electricitySeriesChanged();

private:
    DataFetcher* m_dataFetcher;
    QtCharts::QLineSeries* m_weatherSeries;
    QtCharts::QLineSeries* m_eleSeries;
    QString m_weatherType;
    /*
    QtCharts::QLineSeries* m_eleProductionSeries;
    QtCharts::QLineSeries* m_eleConsumptionSeries;
    QtCharts::QLineSeries* m_windProductionSeries;
    QtCharts::QLineSeries* m_nuclearProductionSeries;
    QtCharts::QLineSeries* m_hydroProductionSeries;
    */
    QPointF m_weatherY;
    QPointF m_elelctricityY;
    QDateTime m_start;
    QDateTime m_end;


};

#endif // MODEL_H
