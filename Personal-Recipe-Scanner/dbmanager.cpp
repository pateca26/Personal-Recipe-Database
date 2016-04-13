#include "dbmanager.h"
#include "ui_dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{

    //needed to load the database file. Needs to be //whatever location you have the file in
     //test to see if it's connected or not

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Sqlite3/scanner.db");

    if (!mydb.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (mydb.isOpen())
    {
        mydb.close();
    }
}

bool DbManager::isOpen() const
{
    return mydb.isOpen();
}

bool DbManager::addCharacter(const QString& file)
{
    bool success = false;

    if (!file.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO File (character) VALUES (:character)");
        queryAdd.bindValue(":character", file);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add file failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add character failed: character cannot be empty";
    }

    return success;
}

bool DbManager::removeCharacter(const QString& file)
{
    bool success = false;

    if (characterExists(file))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM File WHERE character = (:character)");
        queryDelete.bindValue(":character", file);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove character failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove character failed: person doesnt exist";
    }

    return success;
}

void DbManager::printAllCharacters() const
{
    qDebug() << "Characters in db:";
    QSqlQuery query("SELECT * FROM file");
    int idName = query.record().indexOf("file");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool DbManager::characterExists(const QString& file) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT character FROM file WHERE character = (:character)");
    checkQuery.bindValue(":character", file);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "character exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllCharacters()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM file");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all character failed: " << removeQuery.lastError();
    }

    return success;
}
