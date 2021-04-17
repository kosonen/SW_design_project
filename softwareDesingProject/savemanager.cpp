#include "savemanager.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

SaveManager::SaveManager(QObject *parent) : QObject(parent)
{

}

void SaveManager::add(QString key, ISaveObject *obj)
{
    m_data.insert({key, obj});
}

void SaveManager::load(QString filePath, QString key, ISaveObject *obj)
{

}

void SaveManager::save(QString filePath)
{
    qDebug() << "SAVING! to"  << filePath;

    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonObject saveData;

    for (auto e : m_data)
    {
        saveData[e.first] = e.second->serialize();
    }

    QJsonDocument saveDoc(saveData);
    saveFile.write(saveDoc.toJson());
}
