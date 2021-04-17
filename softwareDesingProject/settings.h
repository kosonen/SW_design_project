#ifndef DATAREQUESTSETTINGS_H
#define DATAREQUESTSETTINGS_H

#include "isaveobject.h"

#include <QString>
#include <QVector>
#include <QHash>

/**
 * @brief The DataRequestSettings class implements settings needed to build url for datarequest.
 */
class Settings : public ISaveObject
{
public:
    Settings();
    virtual ~Settings() = default;

    void setLocation(QString location);
    QString getLocation();

    void setDatasources(QVector<QString> sources);
    QVector<QString> getDatasources();

    void setTimeWindow(QString startTime, QString endTime);
    QString getStartTime();
    QString getEndTime();

    QHash<QString,QString> getParams();

    virtual QJsonObject serialize() override;
    virtual void deserialize(QJsonObject data) override;

private:
    QHash<QString, QString> m_params;
    QVector<QString> m_dataSources;

};

#endif // DATAREQUESTSETTINGS_H