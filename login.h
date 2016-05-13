#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QtWidgets>
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
    void connClose();

    //connect and open to DB
    bool connOpen();

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_Register_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
