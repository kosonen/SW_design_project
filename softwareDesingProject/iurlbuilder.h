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
     * @brief buildURL
     * @param settings for URL.
     * @param url of datarequest. User must create empty url for this.
     * @return True if building url is successfull, otherwise false.
     */
    virtual bool buildURL(const DataRequestSettings &settings, QUrl &url) = 0;
};

#endif // IURLBUILDER_H
