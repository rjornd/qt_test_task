#include "tabwidget.h"

#include <QApplication>
#include "dbproxy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabWidget w;
    QObject::connect(DBproxy::getInstance(), SIGNAL(dberror(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QStringList)), &w, SLOT(fillAddrBook(QStringList)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswerNames(QMap<int, QString>)), &w, SLOT(fillComboBox(QMap<int, QString>)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(table_model(QSqlTableModel*)), &w, SLOT(setModel(QSqlTableModel*)));
    QObject::connect(&w, SIGNAL(renewTable()), DBproxy::getInstance(), SLOT(renewTable()));
    QObject::connect(&w, SIGNAL(getNames()), DBproxy::getInstance(), SLOT(getNames()));
    QObject::connect(&w, SIGNAL(getContacts(int)), DBproxy::getInstance(), SLOT(getContacts(int)));
    w.show();
    return a.exec();
}
