#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "isaveobject.h"

#include <QObject>
#include <unordered_map>

/**
 * @brief The SaveManager class is responsible for saving and loadig savable
 * objects. Objects are saved and loaded froom a text file.
 */
class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(QObject *parent = nullptr);

    /**
     * @brief add method is used to add new object to save manager so they can
     * be loaded and saved to/from the same file
     * @param key defines the name for the obj
     * @param obj contains the object to be saved
     */
    void add(QString key, ISaveObject* obj);

    /**
     * @brief load is used to load previously added objects from a fle
     * @param filePath contains path to the file to be loaded
     * @return true if loading file was successful, otherwise false
     */
    bool load(QString filePath);

    /**
     * @brief save is used to save previosly added objects to a file
     * @param filePath contains path to the file to save to.
     * @return true if saving file was successful. otherwise false
     */
    bool save(QString filePath);

private:
    std::unordered_map<QString, ISaveObject*> m_data;

};

#endif // SAVEMANAGER_H
