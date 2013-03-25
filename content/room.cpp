
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

string cRoom::getWhiteBoardName (void)
{
    return this->m_whiteboard;
}

void cRoom::setWhiteBoardName (string& sName)
{
    this->m_whiteboard = sName;
}
