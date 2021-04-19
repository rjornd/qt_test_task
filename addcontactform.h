#ifndef ADDCONTACTFORM_H
#define ADDCONTACTFORM_H

#include <QWidget>
#include "prj_group_addrbook.h"
#include <QMessageBox>
namespace Ui {
class addContactForm;
}

class addContactForm : public QWidget
{
    Q_OBJECT

public:
    explicit addContactForm(QWidget *parent = nullptr);
    ~addContactForm();
    void setGroupId(int);
private:
    Ui::addContactForm *ui;
    int groupId = 0;
signals:
    void dbaddContact(Prj_group_addrbook);
private slots:
    void on_pushButton_clicked();
    void closeChanger();
};

#endif // ADDCONTACTFORM_H
