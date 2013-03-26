
/*
 * student.cpp
 */

#include "student.h"

cStudent::cStudent ()
{
}

cStudent::~cStudent ()
{
}

void cStudent::setName (string& s1, string& s2)
{
    m_StuName = s1 + s2;
}

string cStudent::getName (void)
{
    return m_StuName;
}

void cStudent::setAccount (string& acc)
{
    m_AccountName = acc;
}

string cStudent::getAccount (void)
{
    return m_AccountName;
}

void cStudent::setOnLine (bool b)
{
    m_onLine = b;
}

bool cStudent::getOnLine (void)
{
    return m_onLine;
}
