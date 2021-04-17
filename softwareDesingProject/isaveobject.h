#ifndef ISAVEOBJECT_H
#define ISAVEOBJECT_H

#include <QObject>
#include <QJsonObject>

class ISaveObject : public QObject
{
    Q_OBJECT
public:
    explicit ISaveObject(QObject *parent = nullptr) : QObject(parent) {}

    virtual QJsonObject serialize() = 0;
    virtual void deserialize(QJsonObject data) = 0;
};

#endif // ISAVEOBJECT_H
