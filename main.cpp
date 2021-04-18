#include "tabwidget.h"

#include <QApplication>
#include "dbproxy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabWidget w;

    QObject::connect(DBproxy::getInstance(), SIGNAL(dberror(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QString)), &w, SLOT(needUpdate()));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswerContacts(QMap<int, Prj_group_addrbook>)), &w, SLOT(fillAddrBook(QMap<int, Prj_group_addrbook>)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswerNames(QMap<int, QString>)), &w, SLOT(fillComboBox(QMap<int, QString>)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(table_model(QSqlTableModel*)), &w, SLOT(setModel(QSqlTableModel*)));
    QObject::connect(&w, SIGNAL(renewTable(int)), DBproxy::getInstance(), SLOT(renewTable(int)));
    QObject::connect(&w, SIGNAL(getNames()), DBproxy::getInstance(), SLOT(getNames()));
    QObject::connect(&w, SIGNAL(getContacts(int)), DBproxy::getInstance(), SLOT(getContacts(int)));
    QObject::connect(&w,SIGNAL(dbupdateContact(Prj_group_addrbook)),DBproxy::getInstance(),SLOT(dbupdateContact(Prj_group_addrbook)));
    QObject::connect(&w,SIGNAL(dbremoveContact(Prj_group_addrbook)),DBproxy::getInstance(),SLOT(dbremoveContact(Prj_group_addrbook)));
    w.show();
    return a.exec();
}
