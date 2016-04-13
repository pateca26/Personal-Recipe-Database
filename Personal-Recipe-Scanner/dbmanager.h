#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 people.db
 * 2. sqilte> CREATE TABLE people(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Add character data to db
     * @param file - file to add
     * @return true - character added successfully, false - person not added
     */
    bool addCharacter(const QString& file);

    /**
     * @brief Remove character data from db
     * @param file - file to remove.
     * @return true - character removed successfully, false - character not removed
     */
    bool removeCharacter(const QString& file);

    /**
     * @brief Check if file of character "character" exists in db
     * @param character - character to check.
     * @return true - character exists, false - character does not exist
     */
    bool characterExists(const QString& file) const;

    /**
     * @brief Print file of all character in db
     */
    void printAllCharacters() const;

    /**
     * @brief Remove all character from db
     * @return true - all characters removed successfully, false - not removed
     */
    bool removeAllCharacters();

private:
    QSqlDatabase mydb;
};


#endif // DBMANAGER_H
