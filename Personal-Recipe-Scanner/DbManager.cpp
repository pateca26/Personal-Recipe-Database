#include "sqllite.h"
#include "ui_sqllite.h"

SqlLite::SqlLite(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SqlLite)
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

SqlLite::~SqlLite()
{
    delete ui;
}
