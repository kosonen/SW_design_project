#ifndef DATAREQUESTSETTINGS_H
#define DATAREQUESTSETTINGS_H

#include <QString>
#include <QVector>

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

private:
    QString m_location;
    QVector<QString> m_dataSources;

    QString m_startTime;
    QString m_endTime;



};

#endif // DATAREQUESTSETTINGS_H
