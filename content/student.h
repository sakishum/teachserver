
/*
 * student.h
 */

#ifndef	_C_STUDENT_H
#define _C_STUDENT_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class cStudent
{
private:
	string      m_StuName;
	string      m_AccountName;
	bool        m_onLine;

public:
	cStudent ();
	cStudent (string& s1, string& s2, string& acc, bool line):\
		m_StuName (s1+s2), m_AccountName (acc), m_onLine (line) {}
	~cStudent ();

	void setName (string& s1, string& s2);
	string getName (void);

	void setAccount (string& acc);
	string getAccount (void);

	void setOnLine (bool b);
	bool getOnLine (void);
};

#endif //_C_STUDENT_H
