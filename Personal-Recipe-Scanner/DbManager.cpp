#include "sqllite.h"
#include "ui_sqllite.h"

SqlLite::SqlLite(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SqlLite)
{
    ui->setupUi(this);


    //needed to load the database file. Needs to be //whatever location you have the file in
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Sqlite3/scanner.db");
//test to see if it's connected or not
    if(!mydb.open())
    {
        ui->label->setText("Failed to open database");
    }
    else
    {
         ui->label->setText("Connected to database..");
    }
}

SqlLite::~SqlLite()
{
    delete ui;
}
