#include "prj_group_addrbook.h"

Prj_group_addrbook::Prj_group_addrbook()
{

}

QString Prj_group_addrbook::getFamily() {
    return this->family;
}

QString Prj_group_addrbook::getFirstName()
{
    return this->first_name;
}

void Prj_group_addrbook::setFamily(QString family)
{
    this->family = family;
}
void Prj_group_addrbook::setFirstName(QString firstname)
{
    this->first_name = firstname;
}

void Prj_group_addrbook::setId(int id)
{
    this->prj_group_addrbook_id = id;
}
int Prj_group_addrbook::getId()
{
    return this->prj_group_addrbook_id;
}
QString Prj_group_addrbook::toString()
{
    return this->family + " " + this->first_name;
}

int Prj_group_addrbook::getGroupId()
{
    return this->prj_group_id;
}
void Prj_group_addrbook::setGroupId(int id)
{
    this->prj_group_id = id;
}
