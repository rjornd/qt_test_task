#include "updatecontact.h"
#include "ui_updatecontact.h"

updateContact::updateContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updateContact)
{
    ui->setupUi(this);
}

updateContact::~updateContact()
{
    delete ui;
}

void updateContact::setFamily(QString family)
{
    ui->family->setText(family);
}
void updateContact::setFirstName(QString firstname)
{
    ui->firstName->setText(firstname);
}
void updateContact::getContact(Prj_group_addrbook contact)
{
    ui->family->clear();
    ui->firstName->clear();
    setFamily(contact.getFamily());
    setFirstName(contact.getFirstName());
    this->contact = contact;
}

void updateContact::on_decline_clicked()
{
    setFamily(contact.getFamily());
    setFirstName(contact.getFirstName());
}

void updateContact::on_update_clicked()
{
    contact.setFamily(ui->family->text());
    contact.setFirstName(ui->firstName->text());
    emit dbupdateContact(contact);
    this->close();
}

void updateContact::on_deleteContact_clicked()
{
    emit dbremoveContact(contact);
    this->close();
}
