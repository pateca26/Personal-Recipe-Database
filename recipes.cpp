#include "recipes.h"
#include "ui_recipes.h"
#include<QMessageBox>

Recipes::Recipes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recipes)

{
    ui->setupUi(this);

      Login conn;
            if(!conn.connOpen())
            {
                ui->label_sec_status->setText("Failed to connect to DB");
            }
            else
            {
                ui->label_sec_status->setText("Connected to DB");
            }

}

Recipes::~Recipes()
{
    delete ui;
}
QString filename;
void Recipes::on_pushButton_clicked()
{

    Login conn;
    QString rid,recipe,ingredients,instructions;
    rid = ui->rid->text();
    recipe = ui->txt_recipe->text();
    ingredients = ui->lineEdit_Ingredients->text();
    instructions = ui->lineEdit_Instructions->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open DB";
        return;
    }

    //open db
    conn.connOpen();

    //sql query
    QSqlQuery qry;
    qry.prepare("INSERT INTO recipe (rid,recipe,ingredients,instructions) values ('"+rid+"','"+recipe+"','"+ingredients+"','"+instructions+"')");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Save"),tr("Saved"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
}


//Update Recipe
void Recipes::on_pushButton_Edit_clicked()
{
    Login conn;
    QString rid,recipe,ingredients,instructions;
    rid = ui->rid->text();
    recipe = ui->txt_recipe->text();
    ingredients = ui->lineEdit_Ingredients->text();
    instructions = ui->lineEdit_Instructions->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open DB";
        return;
    }

    //open db
    conn.connOpen();

    //sql query
    QSqlQuery qry;
    qry.prepare("UPDATE recipe SET rid = '"+rid+"',recipe = '"+recipe+"' ,ingredients = '"+ingredients+"' ,instructions = '"+instructions+"' where rid = '"+rid+"'");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Update"),tr("Updated"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
    }
}

//load recipe
void Recipes::on_pushButton_load_clicked()
{
    Login conn;
    QString rid;
    rid = ui->lineEdit_Load->text();
    QSqlQueryModel * model = new QSqlQueryModel();

    //open db
    conn.connOpen();

    //SQL query
    QSqlQuery qry;

    qry.prepare("SELECT recipe,ingredients,instructions FROM recipe WHERE rid = '"+rid+"'");

    qry.exec();
    model->setQuery(qry);
    ui->tableView->setModel(model);

    //Close DB
    conn.connClose();
    qDebug() << (model->rowCount());


}

