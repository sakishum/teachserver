
/*
 * course.cpp
 */

#include "course.h"

cCourse :: cCourse ()
{
}

cCourse :: ~cCourse ()
{
}

void cCourse::setName (string& sName)
{
    this->m_name = sName;
}

string cCourse::getName (void)
{
    return m_name;
}
