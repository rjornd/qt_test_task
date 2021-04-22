#include "tabwidget.h"
#include "ui_tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("test task");
    createCompleter();
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::closeEvent(QCloseEvent *)
{
    emit closeChanger();
}

void TabWidget::showEvent(QShowEvent *)
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
    emit getNames();
    emit renewTable(names.key(ui->comboBox->currentText()));
    resizeTables();
}
void TabWidget::needUpdate()
{
    emit getContacts(cur_group_id);
    ui->find->clear();
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
    this->cur_group_id = names.key(name);
    emit getContacts(cur_group_id);
    emit renewTable(cur_group_id);
}

void TabWidget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QVariant v = item->data(Qt::UserRole);
    Prj_group_addrbook contact = v.value<Prj_group_addrbook>();
    updateContact *updDialog = new updateContact();
    QObject::connect(updDialog,SIGNAL(dbupdateContact(Prj_group_addrbook)),this,SIGNAL(dbupdateContact(Prj_group_addrbook)));
    QObject::connect(updDialog,SIGNAL(dbremoveContact(Prj_group_addrbook)),this,SIGNAL(dbremoveContact(Prj_group_addrbook)));
    QObject::connect(this,SIGNAL(closeChanger()),updDialog,SLOT(closeChanger()));
    updDialog->getContact(contact);
    updDialog->show();
}

void TabWidget::on_addcontact_clicked()
{
    addContactForm *form = new addContactForm();
    form->setGroupId(cur_group_id);
    QObject::connect(form,SIGNAL(dbaddContact(Prj_group_addrbook)),this,SIGNAL(dbaddContact(Prj_group_addrbook)));
    QObject::connect(this,SIGNAL(closeChanger()),form,SLOT(closeChanger()));
    form->show();
}

void TabWidget::createCompleter()
{
    QCompleter* completer = new QCompleter(this);
    auto model = ui->listWidget->model();
    completer->setModel(model);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->find->setCompleter(completer);
    QObject::connect(completer, QOverload<const QModelIndex &>::of(&QCompleter::highlighted),
        [=](const QModelIndex &index) {
            completer->setCurrentRow(index.row());
        }
    );
}


void TabWidget::on_find_returnPressed()
{
    Prj_group_addrbook contact = ui->find->completer()->currentIndex().data(Qt::UserRole).value<Prj_group_addrbook>();
    updateContact *updDialog = new updateContact();
    QObject::connect(updDialog,SIGNAL(dbupdateContact(Prj_group_addrbook)),this,SIGNAL(dbupdateContact(Prj_group_addrbook)));
    QObject::connect(updDialog,SIGNAL(dbremoveContact(Prj_group_addrbook)),this,SIGNAL(dbremoveContact(Prj_group_addrbook)));
    QObject::connect(this,SIGNAL(closeChanger()),updDialog,SLOT(closeChanger()));
    updDialog->getContact(contact);
    updDialog->show();
}

void TabWidget::on_pushButton_2_clicked()
{
    if (sort){
           ui->listWidget->sortItems(Qt::DescendingOrder);
           ui->pushButton_2->setText("По убыванию");
       }
       else{
           ui->listWidget->sortItems(Qt::AscendingOrder);
           ui->pushButton_2->setText("По возрастанию");
       }
       sort = !sort;
}
