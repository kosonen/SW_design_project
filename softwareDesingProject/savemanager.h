#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "isaveobject.h"

#include <QObject>
#include <QDebug>
#include <unordered_map>

class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(QObject *parent = nullptr);

    void add(QString key, ISaveObject* obj);

    bool load(QString filePath);
    bool save(QString filePath);

signals:

private:
    std::unordered_map<QString, ISaveObject*> m_data;

};

#endif // SAVEMANAGER_H
