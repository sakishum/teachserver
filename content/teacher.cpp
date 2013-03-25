
/*
 * teacher.cpp
 */

#include "teacher.h"

bool cTeacher::inCourseList (string& sName)
{
    COURSELIST::iterator it;
    for (it = m_CourseList.begin(); it != m_CourseList.end(); it++) {
        if ((*it)->getName() == sName)
            return true;
    }
    return false;
}

void cTeacher::addCourse (string& sName)
{
    string sql, resultStr1;
    char str[500];
    sprintf (str, "SELECT course_name FROM course WHERE course_name = '%s'", sName.c_str());
    sql = str;
    result = m_DB->Query (sql);
    if ((resultStr1 = result->getString ("course_name")) == sName) {
        if (inCourseList (sName)) {
            //LOG::out "course is exists in the courselist
            return;
        }
        else {
            cCourse* tmp = new cCourse;
            m_CourseList.push_back (tmp);
            return;
        }
    }
    else {
        //LOG::out "grade is not exists in the database"
        return;
    }
}

bool cTeacher::delCourse (string& sName)
{
    COURSELIST::iterator it;
    for (it = m_CourseList.begin(); it != m_CourseList.end(); it++) {
        if ((*it)->getName() == sName) {
            m_CourseList.erase (it);
            delete (*it);
            return true;
        }
    }
    //LOG::out "not exist in the CourseList"
    return false;
}

void cTeacher::setAccount (string& sAccount)
{
    this->m_Account = sAccount;
}

string cTeacher::getAccount (void)
{
    return m_Account;
}
