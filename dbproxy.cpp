#include "dbproxy.h"
#include <QVariant>

DBproxy* DBproxy::m_instance=nullptr;
DBproxy::DBproxy() : QObject(nullptr)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/addrbooks.db");
    model = new QSqlTableModel(this);
}

DBproxy* DBproxy::getInstance()
{
    if (m_instance == nullptr) m_instance = new DBproxy();
    return m_instance;
}

void DBproxy::opendb()
{
    if (!db.open())
    {
        emit dberror(db.lastError().text());
    }
    else
    {
        model->setTable("prj_group_addrbook");
        model->setSort(1, Qt::AscendingOrder);
    }
}
void DBproxy::getNames()
{
    QString qry;
    QMap<int,QString> ans = QMap<int,QString>();
        qry="select prj_group_id, name from `prj_group`";
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec(qry)) emit dbanswer(query.lastError().text());
        else
        {
            while (query.next())
            {
                ans.insert(query.value(0).toInt(), query.value(1).toString());
            }
        }
    }
    emit dbanswerNames(ans);
}

void DBproxy::getContacts(int id)
{
    QString qry;
    QMap<int, Prj_group_addrbook> ans;
    qry="select prj_group_addrbook_id, family, first_name from `prj_group_addrbook` where prj_group_id = '%1';";
    qry = qry.arg(id);
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec(qry)) emit dbanswer(query.lastError().text());
        else
        {
            while (query.next())
            {
                Prj_group_addrbook contact;
                contact.setId(query.value(0).toInt());
                contact.setFamily(query.value(1).toString());
                contact.setFirstName(query.value(2).toString());
                ans.insert(query.value(0).toInt(), contact);
            }
        }
    }
    emit dbanswerContacts(ans);
}

void DBproxy::status()
{

}

void DBproxy::renewTable(int i)
{
    opendb();
    model->select();
    model->setFilter("prj_group_id = "+ QString::number(i));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    emit table_model(model);
}

void DBproxy::dbupdateContact(Prj_group_addrbook contact)
{
    QString qUpd;
    qUpd="update prj_group_addrbook set family='%2', first_name='%3'"
         "where prj_group_addrbook_id='%1';";
    if (db.isOpen())
    {
        qUpd = qUpd.arg(contact.getId()).arg(contact.getFamily()).arg(contact.getFirstName());
        QSqlQuery query(db);
        if (!query.exec(qUpd)) emit dberror(query.lastError().text());
        else emit dbanswer(contact.toString() +" "+ "updated" + " in group_id =" + QString::number(contact.getGroupId()));
    }

}

void DBproxy::dbremoveContact(Prj_group_addrbook contact)
{
    QString qDel;
    qDel="delete from prj_group_addrbook "
         "where prj_group_addrbook_id='%1';";
    if (db.isOpen())
    {
        qDel = qDel.arg(contact.getId());
        QSqlQuery query(db);
        if (!query.exec(qDel)) emit dberror(query.lastError().text());
        else emit dbanswer(contact.toString() +" "+"removed" +" from group_id =" + QString::number(contact.getGroupId()));
    }
}
