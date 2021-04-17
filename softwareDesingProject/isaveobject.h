#ifndef ISAVEOBJECT_H
#define ISAVEOBJECT_H

#include <QObject>

class ISaveObject : public QObject
{
    Q_OBJECT
public:
    explicit ISaveObject(QObject *parent = nullptr) : QObject(parent) {}

    virtual QString serialize() = 0;
    virtual void deserialize(QString data) = 0;
};

#endif // ISAVEOBJECT_H
