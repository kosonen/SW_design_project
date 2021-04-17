#include "datacontainer.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

DataContainer::DataContainer(QObject *parent):
    ISaveObject(parent),
    m_category(),
    m_type(),
    m_unit(),
    m_data()
{

}

int DataContainer::size()
{
    return m_data.size();
}

void DataContainer::setType(QString type)
{
    m_type = type;
}

void DataContainer::setUnit(QString unit)
{
    m_unit = unit;
}

void DataContainer::setCategory(QString category)
{
    m_category = category;
}

void DataContainer::addElement(QPointF point)
{
    m_data.append(point);
}

QString DataContainer::getType()
{
    return m_type;
}

QString DataContainer::getUnit()
{
    return m_unit;
}

QString DataContainer::getCategory()
{
    return m_category;
}

QPointF DataContainer::getElement(int i)
{
    return m_data.at(i);
}

QList<QPointF> DataContainer::getData()
{
    return m_data;
}

QJsonObject DataContainer::serialize()
{
    QJsonObject containerData;
    QJsonArray list;

    containerData["type"] = m_type;
    containerData["category"] = m_category;
    containerData["unit"] = m_unit;

    for (auto e : m_data)
    {
        QJsonObject point;
        point["x"] = e.x();
        point["y"] = e.y();
        list.append(point);
    }

    containerData["data"] = list;

    return containerData;
}

void DataContainer::deserialize(QJsonObject data)
{
    qDebug() << data;

    m_type = data["type"].toString();
    m_category = "save";
    m_unit = data["unit"].toString();

    QJsonArray list = data["data"].toArray();

    for (int i = 0; i < list.size(); i++) {
        QJsonObject obj = list[i].toObject();
        QPointF point;
        point.setX(obj["x"].toDouble());
        point.setY(obj["y"].toDouble());
        addElement(point);
    }
}
