#ifndef MODEL_H
#define MODEL_H

#include "datacontainer.h"
#include "settings.h"
#include "datafetcher.h"

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QDateTime>
#include <QValueAxis>
#include <unordered_map>
#include <QPieSeries>

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
    Q_PROPERTY(QtCharts::QPieSeries* pieSeries READ getPieSeries WRITE setPieSeries NOTIFY pieSeriesChanged)

public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    /**
     * @brief Constructor for Model class
     * @param parent = nullptr in QObject parent system
     */
    explicit Model(QObject *parent = nullptr);

    /**
     * @brief gets Weather Series
     * @return private QLineSeries* for weather
     */
    QtCharts::QLineSeries* getWeatherSeries() const;

    /**
     * @brief gets Electricity Series
     * @return private QLineSeries* for electricity
     */
    QtCharts::QLineSeries* getElectricitySeries() const;

    /**
     * @brief gets Saved Series
     * @return private QLineSeries* for saved LineSeries
     */
    QtCharts::QLineSeries* getSavedSeries() const;

    /**
     * @brief gets Start Time
     * @return private start time of Model timeframe
     */
    QDateTime getStartTime();

    /**
     * @brief gets End Time
     * @return private end time of Model timeframe
     */
    QDateTime getEndTime();

    /**
     * @brief gets Weather Y-axis pointer
     * @return private Y-axis pointer
     */
    QtCharts::QValueAxis *getWeatherY();

    /**
     * @brief gets Electricity Y-axis pointer
     * @return private Y-axis pointer
     */
    QtCharts::QValueAxis *getElectricityY();

    /**
     * @brief gets Saved Y-axis pointer
     * @return private Y-axis pointer
     */
    QtCharts::QValueAxis *getSavedY();

    /**
     * @brief gets Pie Series pointer
     * @return private Pie Series pointer
     */
    QtCharts::QPieSeries* getPieSeries() const;

    /**
     * @brief gets Hydro Power Production
     * @return value as QString
     */
    Q_INVOKABLE QString getHydroProduction();

    /**
     * @brief gets Nuclear Power Production
     * @return value as QString
     */
    Q_INVOKABLE QString getNuclearProduction();

    /**
     * @brief get Wind Power Production
     * @return value as QString
     */
    Q_INVOKABLE QString getWindProduction();

    /**
     * @brief set Data Processing method: AVG, Min, Max, NONE
     * @param method to use
     */
    void setDataProcessing(QString method);

    /**
     * @brief gets top and bottom ĺimits of input data
     * @param data: input data
     * @return QPointF with x value at highest point of data
     * and y at lowest
     */
    QPointF getLimits(QList<QPointF> data);

    /**
     * @brief sets Weather Series to new series
     * @param weatherSeries: new series
     */
    void setWeatherSeries(QtCharts::QLineSeries *weatherSeries);

    /**
     * @brief sets Electricity Series to new series
     * @param electricitySeries: new series
     */
    void setElectricitySeries(QtCharts::QLineSeries *electricitySeries);

    /**
     * @brief sets Saved Series to new series
     * @param savedSeries: new series
     */
    void setSavedSeries(QtCharts::QLineSeries *savedSeries);

    /**
     * @brief sets StartTime to new start time
     * @param start: new start time
     */
    void setStartTime(QDateTime start);

    /**
     * @brief set EndTime to new end time
     * @param end: new end time
     */
    void setEndTime(QDateTime end);

    /**
     * @brief set Weather Y-axis to new value
     * @param newValue: new value
     */
    void setWeatherY(QtCharts::QValueAxis* newValue);

    /**
     * @brief set Electricity Y-axis to new value
     * @param newValue: new value
     */
    void setElectricityY(QtCharts::QValueAxis* newValue);

    /**
     * @brief set Saved LineSeries Y-axis to new value
     * @param newValue: new value
     */
    void setSavedY(QtCharts::QValueAxis* newValue);

    /**
     * @brief set Pie Series to new series
     * @param pieseries: new series
     */
    void setPieSeries(QtCharts::QPieSeries* pieseries);

    /**
     * @brief updates Settings object
     * @param settings: reference to Settings object
     * @return true if settings updated succesfully
     */
    bool update(Settings& settings);

    /**
     * @brief gets DataContainer object from key
     * @param key: map key to DataContainer object
     * @return DataContainer object pointer
     */
    DataContainer* getData(QString key);

public slots:

    /**
     * @brief updates Series selected lineSeries with input data
     * @param data: defines series to update and provides new data
     */
    void updateSeries(DataContainer* data);

    /**
     * @brief update Production PieModel with current data
     * @param currentData: updated current data
     */
    void updateProductionPieModel(DataContainer* currentData);

signals:

    /**
     * @brief Emitted when weather series is changed
     */
    void weatherSeriesChanged();

    /**
     * @brief Emitted when electricity series is changed
     */
    void electricitySeriesChanged();

    /**
     * @brief Emitted when saved series is cahnged
     */
    void savedSeriesChanged();

    /**
     * @brief Emitted when start time is changed
     */
    void startTimeChanged();

    /**
     * @brief Emitted when end time is changed
     */
    void endTimeChanged();

    /**
     * @brief Emitted when Y axel for weather data is changed
     */
    void weatherYChanged();

    /**
     * @brief Emitted when Y axel for electricity is changed
     */
    void electricityYChanged();

    /**
     * @brief Emitted when Y axel for saved data is changed
     */
    void savedYChanged();

    /**
     * @brief Emitted when pieseries is changed
     */
    void pieSeriesChanged();


private:
    DataFetcher* m_dataFetcher;
    QtCharts::QLineSeries* m_weatherSeries;
    QtCharts::QLineSeries* m_eleSeries;
    QtCharts::QLineSeries* m_savedSeries;

    QtCharts::QValueAxis* m_weatherY;
    QtCharts::QValueAxis* m_elelctricityY;
    QtCharts::QValueAxis* m_savedY;
    QtCharts::QPieSeries* m_pieseries;
    QDateTime m_start;
    QDateTime m_end;
    std::unordered_map<QString, DataContainer*> m_data;
    QString m_hydroConsumption;
    QString m_nucklearConsumption;
    QString m_windConsumption;

};

#endif // MODEL_H
