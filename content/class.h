
/*
 * class.h
 */

#ifndef _C_CLASS_H
#define _C_CLASS_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "teacher.h"
#include "student.h"
#include "grade.h"
#include "room.h"

class cClass
{
	typedef list<cStudent*> STUDENTLIST;
public:
	void setName (string& sName);
	string& getName (void);

	cClass ();
	~cClass ();

	cRoom* getRoom (void);
    cGrade* getGrade (void);
	cTeacher* getTeacher (void);

	string getRoomName (void);
    string getGradeName (void);
	string getTeacherName (void);

    bool inRoomTeacher (string& name);
	bool inRoomTeacher (cTeacher* tea);

	bool inRoomStudent (string& name);
	bool inRoomStudent (cStudent* stu);

    void joinStudent (string& fName, string& lName, string& account);

	bool enterRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade);
	bool exitRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade);
private:
	cRoom*      m_Room;
	cTeacher*   m_Teacher;
    cGrade*     m_Grade;
	string      m_ClassName;
	STUDENTLIST m_StudentList;
	int         m_IsExist;
	DataBase*   m_DB;
};

#endif //_C_CLASS_H
