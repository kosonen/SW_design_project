#ifndef DEFINES_H
#define DEFINES_H

#include <QHash>
#include <QUrlQuery>

const QHash<QString, QString> SOURCE_TO_API_MAPPING = {
    {"solar", "FINGRID"},
    {"temperature", "FMI"},
    {"wind", "FMI"}
};

const QHash<QString, QString> WEATHER_OPTION_TO_MODEL_MAPPING = {
    {"Wind speed", "wind"},
    {"Temperature", "temperature"},
    {"Humidity", "humidity"}
};

/*const QHash<QString, QString> CONSUMPTION_OPTION_TO_MODEL_MAPPING = {
    {"Nuclear Power", ""},

};*/

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


// Key for Fingrid API
const QString FINGRID_API_KEY = "gMOfLulbYP2rK93hZVoR33Ij2y59Y0Gg3FgrsCaD";
const QString FINGRID_KEY_HEADER = "x-api-key";

// Default query parameters for FMI
const QUrlQuery FMI_QUERY_FORECAST= QUrlQuery(
{
    QPair<QString, QString>("service", "WFS"),
    QPair<QString, QString>("version", "2.0.0"),
    QPair<QString, QString>("request", "getFeature"),
    QPair<QString, QString>("storedquery_id", "fmi::forecast::hirlam::surface::point::simple")
}

);

const QUrlQuery FMI_QUERY_OBSERVATIONS= QUrlQuery(
{
    QPair<QString, QString>("service", "WFS"),
    QPair<QString, QString>("version", "2.0.0"),
    QPair<QString, QString>("request", "getFeature"),
    QPair<QString, QString>("storedquery_id", "fmi::observations::weather")
}
);

#endif // DEFINES_H
