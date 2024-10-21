#ifndef MAINDASHBOARD_H
#define MAINDASHBOARD_H


#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QDebug>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include "checkcd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainDashBoard; }
QT_END_NAMESPACE

class MainDashBoard : public QMainWindow
{
    Q_OBJECT

public:
    MainDashBoard(QWidget *parent = nullptr);
    ~MainDashBoard();
    void Check();

private slots:
    void on_AddButton_2_clicked();

    void on_DeleteButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainDashBoard *ui;
    QSqlDatabase db;
    CheckCD cd;
    void RefreshTable();
    //QSqlTableModel *model = new QSqlTableModel(this);
};
#endif // MAINDASHBOARD_H
