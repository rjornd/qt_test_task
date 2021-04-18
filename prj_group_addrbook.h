#ifndef PRJ_GROUP_ADDRBOOK_H
#define PRJ_GROUP_ADDRBOOK_H

#include <QString>
#include <QVariant>

class Prj_group_addrbook
{

private:
     int prj_group_id;
     int prj_group_addrbook_id;
     QString family;
     QString first_name;
public:
    Prj_group_addrbook();
    int getGroupId();
    void setGroupId(int);
    int getId();
    void setId(int);
    QString getFamily();
    void setFamily(QString);
    QString getFirstName();
    void setFirstName(QString);
    QString toString();

};

Q_DECLARE_METATYPE(Prj_group_addrbook);

#endif // PRJ_GROUP_ADDRBOOK_H
