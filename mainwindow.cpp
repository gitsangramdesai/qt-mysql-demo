#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool InsertRecord(QString Name,QString Country,QString Address)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//Driver
    db.setHostName("localhost");//server
    db.setPort(3306);//port
    db.setDatabaseName("playground");//database name
    db.setUserName("root");//user name
    db.setPassword("sangram#81");//password

    bool ok = db.open();

    QSqlQuery query;
    if (ok){
            query.prepare( "INSERT INTO QT_TEST (PName,PCountry,PAddress) VALUES ( :PName,:PCountry,:PAddress ) ");
            query.bindValue( ":PName", Name);
            query.bindValue( ":PCountry", Country);
            query.bindValue( ":PAddress", Address);

            query.exec();
            db.close();
            return true;
        }
    return false;
}


void MainWindow::on_btnSubmit_clicked()
{
    QMessageBox Msgbox;
    QString Name =ui->txtName->toPlainText();
    QString Address =ui->txtAddress->toPlainText();


    //listbox
    QListWidgetItem *sel_item = ui->lstCountry->currentItem();
    QString Country= sel_item->text();

    bool result = InsertRecord(Name,Country,Address);
    if(result)
    {
      Msgbox.setText("Record Saved Successfully!");
      Msgbox.exec();
    }
    else
    {
        Msgbox.setText("Unable to Save Record");
        Msgbox.exec();
    }

}


void MainWindow::on_btnReset_clicked()
{
    ui->txtAddress->clear();
    ui->txtName->clear();
    ui->lstCountry->reset();
}

