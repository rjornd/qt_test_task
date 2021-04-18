#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    emit sendQuery();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    resizeTables();
}
void MainWindow::resizeTables()
{
    int w = ui->tableView->width()/7;
    for (int i=0; i<7; i++)
        ui->tableView->setColumnWidth(i,w);
}
void MainWindow::setModel(QSqlTableModel* m)
{
    ui->tableView->setModel(m);
    resizeTables();
}

void MainWindow::showMessage(QString m)
{
    QMessageBox * msgBox = new QMessageBox(this);
    msgBox->setText(m);
    msgBox->exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit sendQuery();
    emit renewTable();
    resizeTabls();
}
