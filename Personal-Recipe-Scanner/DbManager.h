#ifndef SQLLITE_H
#define SQLLITE_H


#include <QMainWindow>

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class SqlLite;
}

class SqlLite : public QMainWindow
{
    Q_OBJECT

public:
    explicit SqlLite(QWidget *parent = 0);
    ~SqlLite();

private:
    Ui::SqlLite *ui;
};

#endif // SQLLITE_H
