
/*
 * teacher.h
 */

#ifndef _C_TEACHER_H
#define _C_TEACHER_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "course.h"
#include "database.h"

using namespace std;

class cTeacher
{
	typedef list<cCourse*> COURSELIST;

private:
	COURSELIST  m_CourseList;
	string      m_TeacherName;
    string      m_Account;
	DataBase*   m_DB;

public:
	bool inCourseList (string& sName);

	void addCourse (string& sName);
	bool delCourse (string& sName);

    void setAccount (string& sAccount);
    string getAccount (void);
};

#endif // _C_TEACHER_H
