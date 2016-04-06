#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class DbManager;
}

class DbManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit DbManager(QWidget *parent = 0);
    ~DbManager();

private:
    Ui::DbManager *ui;
};

#endif // DBMANAGER_H
