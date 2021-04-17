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
    m_data[key] = obj;
}

void SaveManager::load(QString filePath)
{
    qDebug() << "Loading! from" << filePath;

    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray saveContent = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveContent));
    QJsonObject saveData = loadDoc.object();

    for (auto key : saveData.keys())
    {
        qDebug() << key;
        QJsonObject content = saveData[key].toObject();
        m_data[key]->deserialize(content);
    }

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
