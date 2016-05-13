#include "recipes.h"
#include "ui_recipes.h"

Recipes::Recipes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recipes)

{
    ui->setupUi(this);
}

Recipes::~Recipes()
{
    delete ui;
}

void Recipes::setUserId(QString id)
{
    userID = id;
}

void Recipes::on_pushButton_Save_clicked()
{
    // check if updating a recipe
    if(!ui->lineEdit_RecipeID->text().isEmpty())
    {
        updateRecipe();
        return;
    }

    // add new recipe
    Login conn;
    bool dbOK = conn.connOpen();
    if(dbOK)
    {
        QString recipe,ingredients,instructions;
        recipe= ui->lineEdit_Name->text();
        ingredients = ui->lineEdit_Ingredients->text();
        instructions = ui->lineEdit_Instructions->text();

        //sql query
        QSqlQuery qry;
        qry.prepare("INSERT INTO RecipeInfo(userID,recipe,ingredients,instructions) values ('"+userID+"','"+recipe+"','"+ingredients+"','"+instructions+"')");

        if(qry.exec())
        {
            QMessageBox::
            QMessageBox::information(this,tr("Save"),tr("Saved"));
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
        }

        //reset variables
        on_pushButton_Clear_clicked();
        on_pushButton_Search_clicked();

        //close connection
        conn.connClose();
    }
    else
        qDebug() << "Unable to connect to database";
}


//Update Recipe
void Recipes::updateRecipe()
{
    Login conn;
    bool dbOK = conn.connOpen();
    if(dbOK)
    {
        QString recipeID, recipe,ingredients,instructions;
        recipeID = ui->lineEdit_RecipeID->text();
        recipe = ui->lineEdit_Name->text();
        ingredients = ui->lineEdit_Ingredients->text();
        instructions = ui->lineEdit_Instructions->text();

        //sql query
        QSqlQuery qry;

        qry.prepare("UPDATE RecipeInfo SET recipe = '"+recipe+"' ,ingredients = '"+ingredients+"' ,instructions = '"+instructions+"' where recipeID = '"+recipeID+"'");

        if(qry.exec())
        {
            QMessageBox::information(this,tr("Update"),tr("Updated"));
            conn.connClose();
        }
        else
        {
            QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        }

        //clear line edits
        on_pushButton_Clear_clicked();
        on_pushButton_Search_clicked();

        //close connection
        conn.connClose();
    }
    else
        qDebug() << "Unable to connect to database";
}

void Recipes::on_tableView_Recipes_clicked(const QModelIndex &index)
{
    ui->lineEdit_RecipeID->setText(index.sibling(index.row(), 0).data().toString());
    ui->lineEdit_Name->setText(index.sibling(index.row(), 1).data().toString());
    ui->lineEdit_Ingredients->setText(index.sibling(index.row(), 2).data().toString());
    ui->lineEdit_Instructions->setText(index.sibling(index.row(), 3).data().toString());
}

void Recipes::on_pushButton_Clear_clicked()
{
    ui->lineEdit_RecipeID->clear();
    ui->lineEdit_Name->clear();
    ui->lineEdit_Ingredients->clear();
    ui->lineEdit_Instructions->clear();
}

void Recipes::on_pushButton_Delete_clicked()
{
    Login conn;
    bool dbOK = conn.connOpen();
    if(dbOK)
    {
        /*deleting a recipe from the list*/
        if (!ui->lineEdit_RecipeID->text().isEmpty())
        {
            QMessageBox::StandardButton reply;

            reply=QMessageBox::question(this,"Delete","Are you sure you want to delete this recipe?",QMessageBox::Yes|QMessageBox::No);

            if(reply==QMessageBox::Yes)
            {
                QString recipeID = ui->lineEdit_RecipeID->text();

                //SQL query
                QSqlQuery qry;

                qry.exec("DELETE FROM RecipeInfo WHERE recipeID = '" + recipeID + "'");

                //Close DB
                conn.connClose();

                on_pushButton_Clear_clicked();
                on_pushButton_Search_clicked();
            }
        }
    }
    else
        qDebug() << "Unable to connect to database";
}

void Recipes::on_pushButton_Search_clicked()
{
    Login conn;
    bool dbOK = conn.connOpen();
    if(dbOK)
    {
        QString search = ui->lineEdit_Search->text();
        QSqlQueryModel * model = new QSqlQueryModel();

        //SQL query
        QSqlQuery qry;
        QString qryString;

        if(!search.isEmpty())
        {
            qryString = "SELECT recipeID,recipe,ingredients,instructions FROM RecipeInfo WHERE userID = '" + userID +
                    "' AND (recipe LIKE '%"+search+"%' OR ingredients LIKE  '%"+search+"%')";
        }
        else
        {
            qryString = "SELECT recipeID,recipe,ingredients,instructions FROM RecipeInfo WHERE userID = '" + userID +"'";
        }

        qry.exec(qryString);
        model->setQuery(qry);

        ui->tableView_Recipes->setModel(model);

        //Close DB
        conn.connClose();
    }
    else
        qDebug() << "Unable to connect to database";
}
