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
    QStringList ans;
    qry="select family from `prj_group_addrbook` where prj_group_id = '%1';";
    qry = qry.arg(id);
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec(qry)) emit dbanswer(query.lastError().text());
        else
        {
            while (query.next())
            {
                ans.append(query.value(0).toString());
            }
        }
    }
    emit dbanswer(ans);
}

void DBproxy::status()
{

}

void DBproxy::renewTable()
{
    opendb();
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    emit table_model(model);
}
