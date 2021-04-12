#include "datacontainer.h"

DataContainer::DataContainer(QObject *parent):
    QObject(parent),
    m_category(),
    m_type(),
    m_unit(),
    m_data()
{

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
