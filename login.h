#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFile>
#include "recipes.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase RDB;

    //close db
    void connClose()
    {
        RDB.close();
        RDB.removeDatabase(QSqlDatabase::defaultConnection);
    }

    //connect and open to DB
    bool connOpen()
    {
        RDB = QSqlDatabase::addDatabase("QSQLITE");
        //This needs to be your file path. Notice the direction of the "/"
        RDB.setDatabaseName("C:/Users/Landon Rehn/Documents/RecipeDB/scanner.db");

        if(!RDB.open())
        {
            qDebug()<<("Failed to connect to DB");
            return false;
        }
        else
        {
            qDebug()<<("Connected to DB");
            return true;
        }
    }

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
   // QSqlDatabase RDB;
};

#endif // LOGIN_H
