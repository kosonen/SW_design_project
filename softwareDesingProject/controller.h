#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datarequestsettings.h"
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
    Q_PROPERTY(QString message NOTIFY invalidSettings)

public:
    explicit Controller(QObject *parent = nullptr);

    /* Called from QML when all data request configurations have been set*/
    Q_INVOKABLE bool requestData();

    /* Sets location for the data sources to be fetched, eg. Tampere */
    Q_INVOKABLE void setLocation(QString value);

    /* Complete list of all desires data sources,
     * eg. {wind, solar, temperature} */
    Q_INVOKABLE void setDataSources(QVector<QString> sources);

    /* All fetched data sources are fit into the same time frame */
    Q_INVOKABLE void setTimeWindow(QString startTime, QString endTime);

    Q_INVOKABLE void setWeatherType(QString newType);

    Q_INVOKABLE void setElectricityType(QString newType);

    Q_INVOKABLE void setAutomaticUpdate(bool status);

    Q_INVOKABLE bool loadData(QString filePath);
    Q_INVOKABLE bool saveData(QString filePath, QString dataSource);

    Q_INVOKABLE QString getPopupError();

    void setModel(Model* model);

Q_SIGNALS:
    void invalidSettings(QString message);

private:
    SettingsCheck checkSettings();
    void handleSettingCheck(SettingsCheck settingsStatus);
    QDateTime getCurrentDate();

    DataRequestSettings m_settings;
    Model* m_model;
    QTimer m_updateTimer;
    SaveManager m_saveManager;
    QString m_error;
};

#endif // CONTROLLER_H
