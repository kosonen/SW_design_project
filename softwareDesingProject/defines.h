#ifndef DEFINES_H
#define DEFINES_H

#include <QHash>
#include <QUrlQuery>

const QHash<QString, QString> SOURCE_TO_API_MAPPING = {
    {"temperature", "FMI"},
    {"windspeedms", "FMI"},
    {"humidity", "FMI"},
    {"TotalCloudCover", "FMI"},
    {"Wind power",  "FINGRID"},
    {"Nuclear power", "FINGRID"},
    {"Hydro power", "FINGRID"},
    {"Energy consumption", "FINGRID"},
    {"Energy production", "FINGRID"}
};


const QHash<QString, int> LINE_SERIES_MAPPING = {
    {"Temperature",     1},
    {"Wind speed",      2},
    {"Humidity",        3},
    {"TotalCloudCover", 4},
    {"Hydro power",     5},
    {"Wind power",      6},
    {"Nuclear power",   7}
};


const QHash<QString, QString> WEATHER_OPTION_TO_MODEL_MAPPING = {
    {"Wind speed", "windspeedms"},
    {"Temperature", "temperature"},
    {"Humidity", "humidity"},
    {"TotalCloudCover", "TotalCloudCover"}
};


const QHash<QString, QPair<QString, QString>> CONSUMPTION_OPTION_TO_MODEL_MAPPING = {
    {"Hydro power",         QPair<QString, QString>("191", "")},
    {"Wind power",          QPair<QString, QString>("75", "245")},
    {"Nuclear power",       QPair<QString, QString>("188", "")},
    {"Energy consumption",  QPair<QString, QString>("124", "166")},
    {"Energy production",   QPair<QString, QString>("74", "242")}
};

const QList<QString> PRODUCTION_METHODS_FOR_PIE_MODEL =
    {"Hydro power", "Wind power", "Nuclear power"};

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


const QHash<QString, QString> FMI_QUERY_TO_FINGRID_QUERY_PARAMETER_MAPPING = {
    {STARTIME, "start_time"},
    {ENDTIME,"end_time"}
};

const QHash<QString, QString> FMI_SOURCE_TO_UNIT_MAPPING = {
    {"temperature", "°C"},
    {"windspeedms", "m/s"},
    {"humidity", "%"},
    {"TotalCloudCover", ""}
};

const QString FINGRID_UNIT_NAME = "MWh/h";



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
    QPair<QString, QString>("storedquery_id", "fmi::observations::weather::simple")
}


);

#endif // DEFINES_H
