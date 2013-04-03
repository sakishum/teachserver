
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
#include "database.h"
#include "SQL.h"

#include "course.h"

#include "HandleMessage.h"

class CClass
{
	typedef map<int, CStudent*> STUDENTMAP;
    typedef list<CCourse*> COURSELIST;

public:
	 CClass(int id, string class_name, string white_board);
	~CClass ();

    //friend bool CHandleMessage::postTeacherToAllStudent (Buf* p, enum CommandType iCommandType);
    friend class CHandleMessage;

    int  get_class_id();
    void set_teacher_fd(int fd);
    void set_white_fd(int fd);
    void add_student(int fd, CStudent* pstudent);

    CStudent* get_student_by_fd (int fd);
    CTeacher* get_teacher_by_fd (int fd);
    CCourse * get_course_by_name (string course_name);
    CCourse * get_course_by_id (int id);

    void add_course (CCourse *);

    int  get_teacher_fd ();
    int  get_white_fd ();

    CClass* get_class_by_fd (int fd);

private:
    CTeacher m_teacher;
    int m_class_id;
    int m_teacher_fd;
    int m_white_fd;
    string m_class_name;
    string m_white_board;
    STUDENTMAP m_student_map;
    COURSELIST m_course_list;
};

#endif //_C_CLASS_H
