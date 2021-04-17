#ifndef MODEL_H
#define MODEL_H

#include "datacontainer.h"
#include "datarequestsettings.h"
#include "datafetcher.h"

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QDateTime>
#include <QValueAxis>
#include <unordered_map>

//enum weatherT {temperature, wind, humidity, NONE};

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* weatherSeries READ getWeatherSeries WRITE setWeatherSeries NOTIFY weatherSeriesChanged)
    Q_PROPERTY(QtCharts::QLineSeries* elecrtricitySeries READ getElectricitySeries WRITE setElectricitySeries NOTIFY electricitySeriesChanged)
    Q_PROPERTY(QtCharts::QLineSeries* savedSeries READ getSavedSeries WRITE setSavedSeries NOTIFY savedSeriesChanged)
    Q_PROPERTY(QDateTime startTime READ getStartTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ getEndTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QtCharts::QValueAxis* weatherY READ getWeatherY WRITE setWeatherY NOTIFY weatherYChanged)
    Q_PROPERTY(QtCharts::QValueAxis* electricityY READ getElectricityY WRITE setElectricityY NOTIFY electricityYChanged)
    Q_PROPERTY(QtCharts::QValueAxis* savedY READ getSavedY WRITE setSavedY NOTIFY savedYChanged)
    Q_PROPERTY(QString weatherType READ getWeatherType WRITE setWeatherType NOTIFY weatherTypeChanged)
    Q_PROPERTY(QString electricityType READ getElectricityType WRITE setElectricityType NOTIFY electricityTypeChanged)


public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    QtCharts::QLineSeries* getWeatherSeries() const;
    QtCharts::QLineSeries* getElectricitySeries() const;
    QtCharts::QLineSeries* getSavedSeries() const;
    QDateTime getStartTime();
    QDateTime getEndTime();
    QtCharts::QValueAxis *getWeatherY();
    QtCharts::QValueAxis *getElectricityY();
    QtCharts::QValueAxis *getSavedY();
    QString getWeatherType();
    QString getElectricityType();

    QPointF getLimits(QList<QPointF> data);


    void setWeatherSeries(QtCharts::QLineSeries *weatherSeries);
    void setElectricitySeries(QtCharts::QLineSeries *electricitySeries);
    void setSavedSeries(QtCharts::QLineSeries *savedSeries);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);
    void setWeatherY(QtCharts::QValueAxis* newValue);
    void setElectricityY(QtCharts::QValueAxis* newValue);
    void setSavedY(QtCharts::QValueAxis* newValue);
    void setWeatherType(QString newType);
    void setElectricityType(QString newType);

    bool update(DataRequestSettings& settings);

    DataContainer* getData(QString key);

public slots:
    void updateSeries(DataContainer* data);

signals:

    void weatherSeriesChanged();
    void electricitySeriesChanged();
    void savedSeriesChanged();
    void startTimeChanged();
    void endTimeChanged();
    void weatherYChanged();
    void electricityYChanged();
    void savedYChanged();
    void weatherTypeChanged();
    void electricityTypeChanged();


private:
    DataFetcher* m_dataFetcher;
    QtCharts::QLineSeries* m_weatherSeries;
    QtCharts::QLineSeries* m_eleSeries;
    QtCharts::QLineSeries* m_savedSeries;

    QString m_weatherType;
    QString m_electricityType;

    QtCharts::QValueAxis* m_weatherY;
    QtCharts::QValueAxis* m_elelctricityY;
    QtCharts::QValueAxis* m_savedY;

    QDateTime m_start;
    QDateTime m_end;
    std::unordered_map<QString, DataContainer*> m_data;

};

#endif // MODEL_H
