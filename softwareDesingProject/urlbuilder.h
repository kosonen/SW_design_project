#ifndef URLBUILDER_H
#define URLBUILDER_H

#include "iurlbuilder.h"

class URLBuilder : public IURLBuilder
{
public:

    ~URLBuilder();

    static URLBuilder* getInstance();

    bool buildURL(const DataRequestSettings &settings, QUrl &url) override;

private:
    URLBuilder();

    static URLBuilder* s_urlBuilder;
};


#endif // URLBUILDER_H
