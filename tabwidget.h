#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QSqlTableModel>
#include <QMessageBox>

#include <QListWidgetItem>
#include "updatecontact.h"
namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT
private:
    QMap<int, QString> names;
    QMap<int, Prj_group_addrbook> addrbook;
    void renewComboBox();
    bool firstcall = true;
public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();
public:
    void resizeEvent(QResizeEvent *);
    void resizeTables();
    void showEvent(QShowEvent *) override;
private slots:
      void setModel(QSqlTableModel*);
      void showMessage(QString);
      void on_pushButton_clicked();
      void fillComboBox(QMap<int, QString>);
      void on_comboBox_currentTextChanged(const QString &arg1);
      void fillAddrBook(QMap<int, Prj_group_addrbook>);
      void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
      void needUpdate();

signals:
    void renewTable(int);
    void getNames();
    void getContacts(int);
    void getData();
    void dbupdateContact(Prj_group_addrbook);
    void dbremoveContact(Prj_group_addrbook);
private:
    Ui::TabWidget *ui;
};

#endif // TABWIDGET_H
