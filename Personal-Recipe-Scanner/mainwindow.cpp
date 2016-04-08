#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->RecipePreview->setText("Select a Recipe...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addRecipeButton_clicked()
{
    QString imageFile = QFileDialog::getOpenFileName(this, tr("Open Recipe"), QDir::homePath(), tr("Image Files (*.bmp *.gif *.jpeg *.jpg *.png)"));
    ui->RecipePreview->setPixmap(imageFile);
    // TESSERACT STUFF
    ui->listWidget->addItem(imageFile);
}

void MainWindow::on_deleteRecipeButton_clicked()
{
    /*deleting a recipe from the list*/
    QListWidgetItem *itm= ui->listWidget->currentItem();


    QMessageBox::StandardButton reply;

    reply=QMessageBox:: question(this,"Delete",
                           "Are you sure you want do delete "+itm->text()+"?",
                           QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes){
        delete itm;
        // check if current recipe preview
    }

}
