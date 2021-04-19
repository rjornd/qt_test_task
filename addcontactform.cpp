#include "addcontactform.h"
#include "ui_addcontactform.h"

addContactForm::addContactForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addContactForm)
{
    ui->setupUi(this);
}

addContactForm::~addContactForm()
{
    delete ui;
}

void addContactForm::setGroupId(int id){
    this->groupId = id;
}

void addContactForm::on_pushButton_clicked()
{
    Prj_group_addrbook contact;
    if(!(ui->first_name->text().isEmpty() || ui->family->text().isEmpty()))
    {
        contact.setGroupId(groupId);
        contact.setFamily(ui->family->text());
        contact.setFirstName(ui->first_name->text());
        emit dbaddContact(contact);
    }
    else {
        QMessageBox * msgBox = new QMessageBox(this);
        msgBox->setText("Одно из полей пустое");
        msgBox->exec();
    }
}
void addContactForm::closeChanger()
{
    this->close();
}
