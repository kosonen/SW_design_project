#ifndef IURLBUILDER_H
#define IURLBUILDER_H

#include "datarequestsettings.h"
#include <QUrl>

/**
 * @brief The IURLBuilder class acts as an interface to URLBuidler.
 * It builds URL according to the settings.
 */
class IURLBuilder
{
public:

    virtual ~IURLBuilder(){};

    /**
     * @brief buildFMIURL build url to fetch data from FMI API.
     * @param settings for URL.
     * @param url of datarequest. User must create empty url for this.
     * @return True if building url is successfull, otherwise false.
     */
    virtual bool buildFMIURL(DataRequestSettings &settings, QUrl &url, QString source) = 0;

    /**
     * @brief buildFingridURL build url to fetch data from Fingrid API.
     * @param settings for URL.
     * @param url of datarequest. User must create empty url for this.
     * @return True if building url is successfull, otherwise false.
     */
    virtual bool buildFingridURL(DataRequestSettings &settings, QUrl &url, QString source) = 0;
};

#endif // IURLBUILDER_H
