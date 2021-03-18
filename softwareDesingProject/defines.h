#ifndef DEFINES_H
#define DEFINES_H

#include <QHash>

const QHash<QString, QString> SOURCE_TO_API_MAPPING = {
    {"solar", "FINGRID"},
    {"temperature", "FMI"},
    {"wind", "FMI"}
};

// Aliases for query parameters
const QString LOCATION = "place";
const QString STARTIME = "starttime";
const QString ENDTIME = "endtime";
const QString TIMESTEP = "timestep";
const QString PARAMETERS = "parameters";
const QString CRS = "crs";
const QString BBOX = "bbox";
const QString FMISID = "fmisid";
const QString MAXLOCATIONS = "maxlocations";
const QString GEO_ID = "geoid";
const QString WMO = "wmo";
const QString TIMEZONE = "timezone";

#endif // DEFINES_H
