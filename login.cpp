#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::connClose()
{
    RDB.close();
    RDB.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Login::connOpen()
{
    RDB = QSqlDatabase::addDatabase("QSQLITE");
    //This needs to be your file path. Notice the direction of the "/"
    RDB.setDatabaseName("C:/Users/Danro/Downloads/RecipeDB/data/RecipeDB.db");

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

void Login::on_pushButton_Login_clicked()
{
    bool dbOK = this->connOpen();
    if(dbOK)
    {
        QString Username,Password;
        Username = ui->lineEdit_Username->text();
        Password = ui->lineEdit_Password->text();

        QSqlQuery qry(RDB);
        qry.prepare("SELECT * FROM UserInfo WHERE username = '"+Username+"' and password = '"+Password+"'");

        if(qry.exec())
        {
            int count = 0;
            while(qry.next())
            {
                count++;
            }
            if(count == 1)
            {
                ui->label->setText("Username and Password is correct");
                this->hide();
                Recipes recipes;
                QSqlQuery userQry;
                userQry.exec("SELECT userID FROM UserInfo WHERE username = '" + Username + "'");
                userQry.next();
                QSqlRecord record = userQry.record();
                recipes.setUserId(record.value("userID").toString());
                connClose();
                recipes.setModal(true);
                recipes.exec();
            }
            if(count > 1)
            {
                ui->label->setText("Duplicate Username and Password");
                connClose();
            }
            if(count < 1)
            {
                ui->label->setText("Username and/or Password invalid");
                connClose();
            }
        }
    }
    else
        qDebug() << "Unable to connect to database";
}

void Login::on_pushButton_Register_clicked()
{
    bool dbOK = this->connOpen();
    if(dbOK)
    {
        QString Username,Password;
        Username = ui->lineEdit_Username->text();
        Password = ui->lineEdit_Password->text();

        QSqlQuery qry;
        qry.prepare("SELECT * FROM UserInfo WHERE username = '"+Username+"'");

        if(qry.exec())
        {
            int count = 0;
            while(qry.next())
            {
                count++;
            }
            if(count >= 1)
            {
                ui->label->setText("Duplicate Username");
                connClose();
            }
            if(count == 0)
            {
                ui->label->setText("Registered");
                this->hide();
                Recipes recipes;
                QSqlQuery userQry;
                userQry.exec("INSERT INTO UserInfo(username,password) VALUES ('" + Username + "','" + Password + "')");
                userQry.exec("SELECT userID FROM UserInfo WHERE username = '" + Username + "'");
                userQry.next();
                QSqlRecord record = userQry.record();
                recipes.setUserId(record.value("userID").toString());
                connClose();
                recipes.setModal(true);
                recipes.exec();
            }
        }
    }
    else
        qDebug() << "Unable to connect to database";
}
