#ifndef DBPROXY_H
#define DBPROXY_H

#endif // DBPROXY_H

#include <QObject>
#include <QtSql>

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
    void dbanswer(QStringList);
    void table_model(QSqlTableModel*);
public:
    DBproxy();
    static DBproxy* getInstance();

public slots:
    void renewTable();
    void status();
    void opendb();
    void getNames();
    void getContacts(int);
};
