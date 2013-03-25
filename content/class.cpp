
/*
 * class.cpp
 */

#include "class.h"


void cClass::setName (string& sName)
{
    m_ClassName = sName;
}

string cClass::getName (void)
{
    return m_ClassName;
}

cClass::cClass ()
{
    m_Room = new cRoom;
    m_Teacher = new cTeacher;
}

cClass::~cClass ()
{
    if (m_Room)
        delete m_Room;
    if (m_Teacher)
        delete m_Teacher;
    STUDENTLIST::iterator it;
    for (it = m_StudentList.begin(); it != m_StudentList.end(); it++) {
        m_StudentList.erase (it);
        delete (*it); 
    }
}

cRoom* cClass::getRoom (void)
{
    return m_Room;
}

cTeacher* cClass::getTeacher (void)
{
    return m_Teacher;
}

string cClass::getRoomName (void)
{
    return this->m_Room->getName();
}

string cClass::getTeacherName (void)
{
    return this->m_Teacher->getName();
}

string cClass::getGradeName (void)
{
    return this->m_Grade->getName();
}

cGrade* cClass::getGrade (void)
{
    return this->m_Grade;
}

bool cClass::inRoomTeacher (cTeacher* tea)
{
    return this->inRoomTeacher (tea->getName());
}

bool cClass::inRoomTeacher (string& name)
{
    return this->getTeacher()->getName() == name ? \
           true : false;
}

bool cClass::inRoomStudent (string& name)
{
    STUDENTLIST::iterator it;
    for (it = m_StudentList.begin(); it != m_StudentList.end(); it++) {
        if ((*it)->getName() == name)
            return true;
    }
    return false;
}

bool cClass::inRoomStudent (cStudent* stu)
{
    return (this->inRoomStudent (stu->getName()));
}

bool cClass::enterRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade)
{
    int resultInt;
    string resultStr1, resultStr2, resultStr3, resultStr4, resultStr5;
    char str[500];
    ResultSet* result;
    string sql;

    sprintf (str, "SELECT count(*) AS COUNT FROM class WHERE class_name = '%s'", sClass);
    sql = str;
    result = m_DB->Query (sql);
    if ((resultInt = result->getInt ("COUNT")) > 0)
        this->m_ClassName = sClass;
    else {
        //LOG::out "class name is not exists in the database"
        return false;
    }

    sprintf (str, "SELECT classroom_name, white_board FROM classroom WHERE classroom_name = '%s'", sRoom);
    sql = str;
    result = m_DB->Query (sql);
    if ((resultStr1 = result->getString ("classroom_name")) == sRoom) {
        resultStr2 = result->getString ("white_board");
        this->m_Room->setName (resultStr1);
        this->m_Room->setWhiteBoard (resultStr2);
    }
    else {
        //LOG::out "classroom is not exists in the database"
        return false;
    }

    sprintf (str, "SELECT * FROM teacher WHERE account = '%s'", sTeacher);
    sql = str;
    result = m_DB->Query (sql);
    if ((resultStr1 = result->getString ("account")) == sTeacher) {
        this->m_Teacher->setAccount (resultStr1);
        resultStr2 = result->getString ("first_name");
        resultStr3 = result->getString ("last_name");
        this->m_Teacher->setName (resultStr2, resultStr3);
    }
    else {
        //LOG::out "teacher is not exists in the database"
        return false;
    }

    sprintf (str, "SELECT grade_name FROM grade WHERE grade_name = '%s'", sGrade);
    sql = str;
    result = m_DB->Query (sql);
    if ((resultStr1 = result->getString ("grade_name")) == sGrade) {
        this->m_Grade->setName (sGrade);
    }
    else {
        //LOG::out "grade is not exists in the database"
        return false;
    }

    sprintf (str, "SELECT stu.first_name, stu.last_name, stu.account, cla.class_name, gra.grade_name " \
                  "FROM student AS stu, class AS cla, grade AS gra " \
                  "WHERE stu.class_id = cla.class_id " \
                  "AND stu.grade_id = gra.grade_id " \
                  "AND gra.grade_name = '%s' " \
                  "AND cla.class_name = '%s'", sGrade, sClass);
    sql = str;
    result = m_DB->Query (sql);
    while (result->next ()) {
        if ((resultStr1 = result->getString ("grade_name")) == sGrade ||
            (resultStr2 = result->getString ("class_name")) == sClass)
        {
            resultStr3 = result->getString ("first_name");
            resultStr4 = result->getString ("last_name");
            resultStr5 = result->getString ("account");
            joinStudent (resultStr3, resultStr4, resultStr5);
        }
    }

    return true;
}

void cClass::joinStudent (string& fName, string& lName, string& account)
{
    cStudent* tmp = new cStudent;
    tmp->setName (fName, lName);
    tmp->setAccount (account);
    m_StudentList->push_back (tmp);
}

bool cClass::exitRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade)
{
    STUDENTLIST::iterator it, it2;
    for (it = m_StudentList.begin(); it != m_StudentList.end();) {
        it2 = it++;
        m_StudentList.erase (it2);
        delete (*it2);
    }
    return true;
}
