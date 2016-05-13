#ifndef RECIPES_H
#define RECIPES_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Recipes;
}

class Recipes : public QDialog
{
    Q_OBJECT

public:

    explicit Recipes(QWidget *parent = 0);
    ~Recipes();
    void setUserId(QString id);
    void updateRecipe();

private slots:
    void on_pushButton_Save_clicked();

    void on_tableView_Recipes_clicked(const QModelIndex &index);

    void on_pushButton_Clear_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Search_clicked();

private:
    Ui::Recipes *ui;
    QString userID;
};

#endif // RECIPES_H
