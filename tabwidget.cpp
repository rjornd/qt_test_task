#include "tabwidget.h"
#include "ui_tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::showEvent(QShowEvent *e)
{
    if (!firstcall) return;
    emit getNames();
    emit renewTable();

    this->firstcall = false;
}


void TabWidget::resizeEvent(QResizeEvent *e)
{

    QTabWidget::resizeEvent(e);
    resizeTables();
}

void TabWidget::resizeTables()
{
    int w = ui->tableView->width()/7;
    for (int i=0; i<7; i++)
        ui->tableView->setColumnWidth(i,w);
}
void TabWidget::setModel(QSqlTableModel* m)
{
    ui->tableView->setModel(m);
    resizeTables();
}

void TabWidget::renewComboBox(){

    ui->comboBox->clear();
    foreach (QString name, this->names) {
        ui->comboBox->addItem(name);
    }
}

void TabWidget::fillComboBox(QMap<int, QString> map)
{
    this->names.clear();
    this->names = map;
    renewComboBox();
}

void TabWidget::showMessage(QString m)
{
    QMessageBox * msgBox = new QMessageBox(this);
    msgBox->setText(m);
    msgBox->exec();
}

void TabWidget::on_pushButton_clicked()
{
    emit getNames();
    emit renewTable();
    resizeTables();
}

void TabWidget::fillAddrBook(QStringList addrbook)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(addrbook);
}

void TabWidget::on_comboBox_currentTextChanged(const QString &name)
{
    emit getContacts(names.key(name));
}
