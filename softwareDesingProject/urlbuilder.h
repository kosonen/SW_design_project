#ifndef URLBUILDER_H
#define URLBUILDER_H

#include "iurlbuilder.h"

class URLBuilder : public IURLBuilder
{
public:

    ~URLBuilder();

    static URLBuilder* getInstance();

    bool buildFMIURL(DataRequestSettings &settings, QUrl &url, QString source ) override;
    bool buildFingridURL(const DataRequestSettings &settings, QUrl &url, QString source) override;

private:
    URLBuilder();
    QUrlQuery getBaseQuery(const QString &startTime,const QString &endTime);

    static URLBuilder* s_urlBuilder;
};


#endif // URLBUILDER_H
