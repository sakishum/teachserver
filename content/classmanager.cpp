
/*
 * classmanager.cpp
 */

#include "classmanager.h"

cClassManager* cClassManager::m_ClassManager = NULL;

cClassManager* cClassManager::getInstance (void)
{
	if (NULL == m_ClassManager)
		m_ClassManager = new cClassManager;
	return m_ClassManager; 

}

bool cClassManager::enterRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade)
{
	if (!findClass (sClass, sRoom, sTeacher, sGrade)) {
		cClass* tmp = new cClass;
		tmp->enterRoom (sClass, sRoom, sTeacher, sGrade);
		m_ClassList.push_back (tmp);
		return true;
	}
	else {
		// LOG::out "class, room, teacher, grade";
		return false;
	}
}

bool cClassManager::exitRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade)
{
#if 1
	CLASSLIST::iterator it;
	for (it = m_ClassList.begin(); it != m_ClassList.end(); it++) {
		if ((*it)->getRoom()->getName() == sRoom &&
			(*it)->getTeacher()->getAccount() == sTeacher &&
			(*it)->getName() == sClass &&
			(*it)->getGrade()->getName() == sGrade)
		{
			m_ClassList.erase (it);
			(*it)->exitRoom(sClass, sRoom, sTeacher, sGrade);
			delete (*it);
			return true;
		}
	}
	return false;
#endif
}

cClass* cClassManager::findClass (string& sClass, string& sRoom, string& sTeacher, string& sGrade)
{
	CLASSLIST::iterator it;
	for (it = m_ClassList.begin(); it != m_ClassList.end(); it++) {
		if ((*it)->getRoom()->getName() == sRoom &&
			(*it)->getTeacher()->getAccount() == sTeacher &&
			(*it)->getName() == sClass &&
			(*it)->getGrade()->getName() == sGrade) {
				return (*it);
		}
	}
	return NULL;
}
