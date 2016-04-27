#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


    if(!connOpen())
    {
        ui->label->setText("Failed to connect to DB");
    }
    else
    {
        ui->label->setText("Connected to DB");
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString Username,Password;
    Username = ui->lineEdit_Username->text();
    Password = ui->lineEdit_Password->text();

    if(!connOpen())
    {
        qDebug()<<"Failed to open DB";
        return;
    }

    connOpen();
    QSqlQuery qry;
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
            connClose();
            this->hide();
            Recipes recipes;
            recipes.setModal(true);
            recipes.exec();
        }
        if(count > 1)
        {
            ui->label->setText("Duplicate Username and Password");
        }
        if(count < 1)
        {
            ui->label->setText("Username and Password is not correct");
        }

    }
}
