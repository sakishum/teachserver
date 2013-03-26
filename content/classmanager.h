
/*
 * classmanager.h
 */

#ifndef _C_CLASSMANAGER_H
#define _C_CLASSMANAGER_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "class.h"

using namespace std;

class cClassManager
{
	typedef list<cClass*> CLASSLIST;

public:
	cClassManager* getInstance (void);
	~cClassManager () {};

	bool enterRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade);
	bool exitRoom (string& sClass, string& sRoom, string& sTeacher, string& sGrade);
	cClass* findClass (string& sClass, string& sRoom, string& sTeacher, string& sGrade);

private:
	cClassManager () {}
	CLASSLIST m_ClassList;
	static cClassManager* m_ClassManager;
};

#define CLASSMANAGER cClassManager::getInstance()

#endif //_C_CLASSMANAGER_H
