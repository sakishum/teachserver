
/*
 * grade.cpp
 */

#include "grade.h"

string cGrade::getName (void)
{
    return this->m_name;
}

void cGrade::setName (string& sName)
{
    this->m_name = sName;
}
