#ifndef UPDATECONTACT_H
#define UPDATECONTACT_H

#include <QWidget>
#include "prj_group_addrbook.h"
namespace Ui {
class updateContact;
}

class updateContact : public QWidget
{
    Q_OBJECT

public:
    explicit updateContact(QWidget *parent = nullptr);
    ~updateContact();
    void setFamily(QString);
    void setFirstName(QString);
    void getContact(Prj_group_addrbook);
private slots:
    void on_decline_clicked();

    void on_update_clicked();

    void on_deleteContact_clicked();

signals:
    void dbremoveContact(Prj_group_addrbook);
    void dbupdateContact(Prj_group_addrbook);
private:
    Ui::updateContact *ui;
    Prj_group_addrbook contact;
};

#endif // UPDATECONTACT_H
