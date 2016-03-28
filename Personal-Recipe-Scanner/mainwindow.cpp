#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_clicked()
{
    ui->listWidget->addItem("new item");
}

void MainWindow::on_toolButton_2_clicked()
{
    /*deleting a recipe from the list*/
    QListWidgetItem *itm= ui->listWidget->currentItem();


    QMessageBox::StandardButton reply;

    reply=QMessageBox:: question(this,"Delete",
                           "Are you sure you want do delete "+itm->text()+"?",
                           QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes){
    delete itm;
    }

}
