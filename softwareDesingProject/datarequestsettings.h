#ifndef DATAREQUESTSETTINGS_H
#define DATAREQUESTSETTINGS_H

#include <QString>
#include <QVector>
#include <QHash>

/**
 * @brief The DataRequestSettings class implements settings needed to build url for datarequest.
 */
class DataRequestSettings
{
public:
    DataRequestSettings();
    ~DataRequestSettings(){};

    void setLocation(QString location);
    QString getLocation();

    void setDatasources(QVector<QString> sources);
    QVector<QString> getDatasources();

    void setTimeWindow(QString startTime, QString endTime);
    QString getStartTime();
    QString getEndTime();

    QHash<QString,QString> getParams();

private:
    QHash<QString, QString> m_params;
    QVector<QString> m_dataSources;



};

#endif // DATAREQUESTSETTINGS_H
