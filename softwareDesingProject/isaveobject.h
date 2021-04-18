#ifndef ISAVEOBJECT_H
#define ISAVEOBJECT_H

#include <QObject>
#include <QJsonObject>

/**
 * @brief The ISaveObject class is an iterface for savable objects
 */
class ISaveObject : public QObject
{
    Q_OBJECT
public:
    explicit ISaveObject(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief serialize produces a QJSsonObject from the state of the class
     * @return the produced QJsonObject
     */
    virtual QJsonObject serialize() = 0;

    /**
     * @brief deserialize sets the state of the class based on a QJsonObject
     * @param data contains the QJsonObject to use
     */
    virtual void deserialize(QJsonObject data) = 0;
};

#endif // ISAVEOBJECT_H
