#ifndef DATAREQUESTSETTINGS_H
#define DATAREQUESTSETTINGS_H

#include "isaveobject.h"

#include <QString>
#include <QVector>
#include <QHash>

/**
 * @brief The DataRequestSettings class contains the global settings needed to build url for datarequest.
 */
class Settings : public ISaveObject
{
public:

    /**
     * @brief Constructor for Settings class
     */
    Settings();
    virtual ~Settings() = default;

    /**
     * @brief Set location for weather data request
     * @param location for data request
     */
    void setLocation(QString location);
    /**
     * @brief Getter function for current location
     * @return location of settings
     */
    QString getLocation();

    /**
     * @brief Set data sources for datasources. Tells what kind of information is fetched.
     * In example temperature, humidity, wind power etc.
     * @param sources to fetch
     */
    void setDatasources(QVector<QString> sources);

    /**
     * @brief Getter for datasources
     * @return Datasources
     */
    QVector<QString> getDatasources();

    /**
     * @brief Set time window for data request
     * @param startTime start time for entrys
     * @param endTime end time for entrys
     */
    void setTimeWindow(QString startTime, QString endTime);

    /**
     * @brief Getter for start time of data request
     * @return start time of data request
     */
    QString getStartTime();

    /**
     * @brief Getter for end time of data request
     * @return end time of data request
     */
    QString getEndTime();

    /**
     * @brief set Data Processing method: AVG, MIN, MAX, NONE
     * @param method to use
     */
    void setDataProcessing(QString method);

    /**
     * @brief get Data Processing method: AVG, MIN, MAX, NONE
     * @return method to use
     */
    QString getDataProcessing();

    /**
     * @brief Getter for all parameters of data request except data sources
     * @return Parameters
     */
    QHash<QString,QString> getParams();

    virtual QJsonObject serialize() override;
    virtual void deserialize(QJsonObject data) override;

private:
    QHash<QString, QString> m_params;
    QVector<QString> m_dataSources;

};

#endif // DATAREQUESTSETTINGS_H
