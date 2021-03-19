#ifndef MODEL_H
#define MODEL_H

#include "datarequestsettings.h"
#include "iurlbuilder.h"
#include "urlbuilder.h"
#include "api.h"

#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:

    /*Here should probably be the Q_PROPERTY variables that are linked to QML*/

    explicit Model(QObject *parent = nullptr);

    bool update(DataRequestSettings settings);

signals:

private:
    IURLBuilder* m_urlBuilder;
    API m_requestAPI;

};

#endif // MODEL_H
