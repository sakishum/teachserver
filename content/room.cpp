/*
 * class.cpp
 */

#include "room.h"

CRoom::CRoom(int id, string class_name, string white_board) {
    m_room_id = id;
    m_room_name = class_name;
    m_white_board = white_board;
}

int CRoom::get_room_id() {
    return m_room_id;
}

void CRoom::set_teacher_fd(int fd) {
    m_teacher_fd = fd;
}

void CRoom::set_white_fd(int fd) {
    m_white_fd = fd;
}

void CRoom::add_student(int fd, CStudent* pstudent) {
    m_student_map.insert(pair<int, CStudent*>(fd, pstudent));
}

CStudent* CRoom::get_student_by_fd (int fd)
{
    STUDENTMAP::iterator it = m_student_map.find(fd);
    if (it != m_student_map.end()) {
        return it->second;
    }
    return NULL;
}

CTeacher* CRoom::get_teacher_by_fd (int fd)
{
    if (fd == this->m_teacher_fd)
        return &m_teacher;
    else
        return NULL;
}

CCourse* CRoom::get_course_by_name (string course_name)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it!= m_course_list.end (); it++) {
        if ((*it)->getName () == course_name)
            return (*it);
    }
    return NULL;
}

CCourse* CRoom::get_course_by_id (int id)
{
    COURSELIST::iterator it;
    for (it = m_course_list.begin (); it != m_course_list.end (); it++) {
        if ((*it)->getId() == id)
            return (*it);
    }
    return NULL;
}

void CRoom::add_course (CCourse* pCourse)
{
    if (pCourse != NULL)
        m_course_list.push_back (pCourse);
}

int CRoom::get_teacher_fd ()
{
    return this->m_teacher_fd;
}

int CRoom::get_white_fd ()
{
    return this->m_white_fd;
}

CRoom* CRoom::get_room_by_fd (int fd)
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
