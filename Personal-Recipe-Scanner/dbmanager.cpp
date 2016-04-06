#include "dbmanager.h"
#include "ui_dbmanager.h"

DbManager::DbManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DbManager)
{
    ui->setupUi(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Sqlite3/scanner.db");

    if(!mydb.open())
    {
        ui->label->setText("Failed to open database");
    }
    else
    {
         ui->label->setText("Connected to database..");
    }
}

DbManager::~DbManager()
{
    delete ui;
}
