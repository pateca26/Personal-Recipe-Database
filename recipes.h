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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Edit_clicked();

    void on_pushButton_load_clicked();



private:
    Ui::Recipes *ui;

};

#endif // RECIPES_H
