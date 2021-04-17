#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include "isaveobject.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QPointF>

class DataContainer : public ISaveObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = nullptr);

    virtual ~DataContainer() = default;

    void setType(QString type);
    void setUnit(QString unit);
    void setCategory(QString category);
    void addElement(QPointF point);

    QString getType();
    QString getUnit();
    QString getCategory();
    QPointF getElement(int i);
    QList<QPointF> getData();

    int size();
//    void clear();

    virtual QString serialize() override;
    virtual void deserialize(QString data) override;

private:
    QString m_category;
    QString m_type;
    QString m_unit;
    QList<QPointF> m_data;
};

#endif // DATACONTAINER_H

