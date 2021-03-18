#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datarequestsettings.h"
#include "iurlbuilder.h"
#include <QObject>

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

private:
    /* Maybe add own class for parameter settings */
    DataRequestSettings m_settings;
    IURLBuilder* m_urlBuilder;
signals:

};

#endif // CONTROLLER_H
