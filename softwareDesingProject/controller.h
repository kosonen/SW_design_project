#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datarequestsettings.h"


#include "model.h"

#include <QObject>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
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

    void setModel(Model* model);

signals:

private:
    DataRequestSettings m_settings;
    Model* m_model;
    QTimer m_updateTimer;
};

#endif // CONTROLLER_H
