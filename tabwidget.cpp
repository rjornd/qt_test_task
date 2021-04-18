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
    emit renewTable(names.key(ui->comboBox->currentText()));
    resizeTables();
    this->firstcall = false;
}


void TabWidget::resizeEvent(QResizeEvent *e)
{
    QTabWidget::resizeEvent(e);
    resizeTables();
}

void TabWidget::resizeTables()
{
    int w = ui->tableView->width()/2;
    for (int i=0; i<10; i++)
        ui->tableView->setColumnWidth(i,w);
}
void TabWidget::setModel(QSqlTableModel* m)
{
    resizeTables();
    ui->tableView->setModel(m);
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
    needUpdate();
}
void TabWidget::needUpdate()
{
    emit getNames();
    emit renewTable(names.key(ui->comboBox->currentText()));
    resizeTables();
}
void TabWidget::fillAddrBook(QMap<int, Prj_group_addrbook> addrbook)
{
    this->addrbook.clear();
    this->addrbook = addrbook;
    ui->listWidget->clear();
    foreach (Prj_group_addrbook contact, addrbook) {
        auto *item = new QListWidgetItem(contact.toString());
        contact.setGroupId(names.key(ui->comboBox->currentText()));
        QVariant v;
        v.setValue(contact);
        item->setData(Qt::UserRole, v);
        item->setText(contact.toString());
        ui->listWidget->addItem(item);
    }
}

void TabWidget::on_comboBox_currentTextChanged(const QString &name)
{
    emit getContacts(names.key(name));
    emit renewTable(names.key(name));
}

void TabWidget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QVariant v = item->data(Qt::UserRole);
    Prj_group_addrbook contact = v.value<Prj_group_addrbook>();
    updateContact *updDialog = new updateContact();
    QObject::connect(updDialog,SIGNAL(dbupdateContact(Prj_group_addrbook)),this,SIGNAL(dbupdateContact(Prj_group_addrbook)));
    QObject::connect(updDialog,SIGNAL(dbremoveContact(Prj_group_addrbook)),this,SIGNAL(dbremoveContact(Prj_group_addrbook)));
    updDialog->getContact(contact);
    updDialog->show();
}
