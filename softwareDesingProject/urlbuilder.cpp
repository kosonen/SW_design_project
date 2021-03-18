#include "urlbuilder.h"

/*
URLBuilder::URLBuilder()
{

}*/

URLBuilder* URLBuilder::s_urlBuilder = nullptr;

URLBuilder::~URLBuilder()
{
    s_urlBuilder = nullptr;
}

URLBuilder *URLBuilder::getInstance()
{
    if(s_urlBuilder == nullptr)
    {
        s_urlBuilder = new URLBuilder;
    }
    return  s_urlBuilder;
}

bool URLBuilder::buildURL(const DataRequestSettings &settings, QUrl &url)
{

}

URLBuilder::URLBuilder()
 {

}
