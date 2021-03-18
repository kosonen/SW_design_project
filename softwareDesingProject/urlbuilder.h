#ifndef URLBUILDER_H
#define URLBUILDER_H

#include "iurlbuilder.h"

class URLBuilder : public IURLBuilder
{
public:

    ~URLBuilder();

    static URLBuilder* getInstance();

    bool buildFMIURL(DataRequestSettings &settings, QString &urlString) override;
    bool buildFingridURL(const DataRequestSettings &settings, QString &urlString) override;

private:
    URLBuilder();

    static URLBuilder* s_urlBuilder;
};


#endif // URLBUILDER_H
