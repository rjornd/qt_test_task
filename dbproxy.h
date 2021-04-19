#ifndef DBPROXY_H
#define DBPROXY_H

#endif // DBPROXY_H

#include <QObject>
#include <QtSql>
#include "prj_group_addrbook.h"
class DBproxy : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;
    static DBproxy* m_instance;
    QSqlTableModel* model;

signals:
    void dberror(QString);
    void dbanswer(QString);
    void dbanswerNames(QMap<int, QString>);
    void dbanswerContacts(QMap<int, Prj_group_addrbook>);
    void table_model(QSqlTableModel*);
public:
    DBproxy();
    static DBproxy* getInstance();

public slots:
    void renewTable(int);
    void status();
    void opendb();
    void getNames();
    void getContacts(int);
    void dbupdateContact(Prj_group_addrbook);
    void dbremoveContact(Prj_group_addrbook);
    void dbaddContact(Prj_group_addrbook);
};
