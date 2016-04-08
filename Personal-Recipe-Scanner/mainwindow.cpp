#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtGui>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->picture_output->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->picture_output->setScaledContents(true);

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

void MainWindow::on_pushButton_clicked()
{
    QString imagefile=QFileDialog::getOpenFileName(
                this,
                tr("Open Image"),
                "/Users/",
                "All files(*.*);;Image files(*.jpg)"
                );

    QPixmap pix(imagefile);
    ui->picture_output->setPixmap(pix);



}
