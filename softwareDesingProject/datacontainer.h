#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include "isaveobject.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QPointF>

/**
 * @brief The DataContainer class contais raw timeseries data and associated
 * metadata.
 */
class DataContainer : public ISaveObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = nullptr);

    virtual ~DataContainer() = default;

    /**
     * @brief setType is used to set container type
     * @param type to set
     */
    void setType(QString type);

    /**
     * @brief setUnit is used to set container unit
     * @param unit to set
     */
    void setUnit(QString unit);

    /**
     * @brief setCategory is used to set container category
     * @param category to set
     */
    void setCategory(QString category);

    /**
     * @brief addElement adds new element to container
     * @param point to be added
     */
    void addElement(QPointF point);

    /**
     * @brief getType returns the unit of this container
     * @return type
     */
    QString getType();

    /**
     * @brief getUnit returns the unit of this container
     * @return unit
     */
    QString getUnit();

    /**
     * @brief getCategory returns the category of this container
     * @return category
     */
    QString getCategory();

    /**
     * @brief getElement returns the i:th element in the datacontainer
     * @param i is the index of returned element
     * @return the QPointF in in that index
     */
    QPointF getElement(int i);

    /**
     * @brief getData returns the internally used datacontainer
     * @return the raw data container
     */
    QList<QPointF> getData();

    /**
     * @brief gets top and bottom ĺimits of input data
     * @return QPointF with x value at highest point of data
     * and y at lowest
     */
    QPointF getLimits();

    /**
     * @brief size returns the number of elements in this container
     * @return number of elements
     */
    int size();

    virtual QJsonObject serialize() override;
    virtual void deserialize(QJsonObject data) override;

private:
    QString m_category;
    QString m_type;
    QString m_unit;
    QList<QPointF> m_data;
};

#endif // DATACONTAINER_H

