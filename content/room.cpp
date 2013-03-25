
/*
 * room.cpp
 */

#include "room.h"

string cRoom::getName (void)
{
    return m_name;
}

void cRoom::setName (string& sName)
{
    this->m_name = sName;
}