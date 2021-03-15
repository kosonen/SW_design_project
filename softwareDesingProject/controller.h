#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    /* Called from QML when all data request configurations have been set*/
    Q_INVOKABLE bool requestData();

    /* Sets search parameters before requesting data
       eg. paramName = Tampere, paramValue = temperature */
    Q_INVOKABLE void setParameter(QString paramName, QString paramValue);
private:
    /* Maybe add own class for parameter settings */
signals:

};

#endif // CONTROLLER_H
