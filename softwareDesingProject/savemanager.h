#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "isaveobject.h"

#include <QObject>

class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(QObject *parent = nullptr);

    void load(QString filePath, QString key, ISaveObject* obj);

signals:

};

#endif // SAVEMANAGER_H
