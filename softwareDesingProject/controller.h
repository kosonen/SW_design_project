#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settings.h"
#include "savemanager.h"


#include "model.h"

#include <QObject>
#include <QTimer>

enum SettingsCheck {
    SC_OK = 0,
    SC_StartTimeGreaterThanEnd,
    SC_NoSources,
    SC_NoForecastForNuclear,
    SC_NoForecastForHydro,
    SC_NoForecastForUnidentifiedSource
};

class Controller : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief constructor for Controller class
     * @param parent = nullptr in QObject parent system
     */
    explicit Controller(QObject *parent = nullptr);

    /**
     * @brief Called from QML, requests Data from API after all data request
     * configurations have been set
     * @return true if operation successful
     */
    Q_INVOKABLE bool requestData();

    /**
     * @brief sets location for the data sources to be fetched, eg. Tampere
     * @param value: new location as QString
     */
    Q_INVOKABLE void setLocation(QString value);

    /**
     * @brief sets complete list of all desires
     * data sources, eg. {wind, solar, temperature}
     * @param sources: list of sources in QVector
     */
    Q_INVOKABLE void setDataSources(QVector<QString> sources);

    /**
     * @brief Sets time window
     * All fetched data sources are fit into the same time frame
     * @param startTime: new start time
     * @param endTime: new end time
     */
    Q_INVOKABLE void setTimeWindow(QString startTime, QString endTime);

    /**
     * @brief enables automatic update timer
     * @param status: true to set timer
     */
    Q_INVOKABLE void setAutomaticUpdate(bool status);

    /**
     * @brief loads Data from given path
     * @param filePath: path to load file
     * @return true if operation is succesful
     */
    Q_INVOKABLE bool loadData(QString filePath);

    /**
     * @brief save Data to given path
     * @param filePath: path to save file
     * @param dataSource: source name to save
     * @return true if operation is successful
     */
    Q_INVOKABLE bool saveData(QString filePath, QString dataSource);

    /**
     * @brief sets Data Processing method
     * eg. MIN, MAX, AVG, NONE
     * @param method: method to set
     */
    Q_INVOKABLE void setDataProcessing(QString method);

    /**
     * @brief get Popup Error string
     * @return Error String
     */
    Q_INVOKABLE QString getPopupError();

    /**
     * @brief sets Model object to control
     * @param model: Model object pointer
     */
    void setModel(Model* model);

    /**
     * @brief sets Settings object to use
     * @param settings: Settings object pointer
     */
    void setSettings(Settings* settings);

Q_SIGNALS:
    void invalidSettings(QString message);

private:
    SettingsCheck checkSettings();
    void handleSettingCheck(SettingsCheck settingsStatus);
    QDateTime getCurrentDate();

    Settings* m_settings;
    Model* m_model;
    QTimer m_updateTimer;
    SaveManager m_saveManager;
    QString m_error;
};

#endif // CONTROLLER_H
