

/*
 * class.cpp
 */

#include "class.h"

CClass::CClass(int id, string class_name, string white_board) {
    m_class_id = id;
    m_class_name = class_name;
    m_white_board = white_board;
}

int CClass::get_class_id() {
    return m_class_id;
}

void CClass::set_teacher_fd(int fd) {
    m_teacher_fd = fd;
}

void CClass::set_white_fd(int fd) {
    m_white_fd = fd;
}

void CClass::add_student(int fd, CStudent* pstudent) {
    m_student_map.insert(pair<int, CStudent*>(fd, pstudent));
}

CStudent* CClass::get_student_by_fd (int fd)
{
    STUDENTMAP::iterator it = m_student_map.find(fd);
    if (it != m_student_map.end()) {
        return it->second;
    }
    return NULL;
}

CTeacher* CClass::get_teacher_by_fd (int fd)
{
    if (fd == this->m_teacher_fd)
        return &m_teacher;
    else
        return NULL;
}

CCourse* CClass::get_course_by_name (string course_name)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it!= m_course_list.end (); it++) {
        if ((*it)->getName () == course_name)
            return (*it);
    }
    return NULL;
}

CCourse* CClass::get_course_by_id (int id)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it != m_course_list.end (); it++) {
        if ((*it)->getId() == id)
            return (*it);
    }
    return NULL;
}

void CClass::add_course (CCourse* pCourse)
{
    if (pCourse != NULL)
        m_course_list.push_back (pCourse);
}

int CClass::get_teacher_fd ()
{
    return this->m_teacher_fd;
}

int CClass::get_white_fd ()
{
    return this->m_white_fd;
}

CClass* CClass::get_class_by_fd (int fd)
{
    STUDENTMAP::iterator it = m_student_map.find(fd);
    if (it != m_student_map.end()) {
        return this;//it->second;
    }
    else if (fd == this->m_teacher_fd)
        return this;
    else if (fd == this->m_white_fd)
        return this;
    else
        return NULL;
}
