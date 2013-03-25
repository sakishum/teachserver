
/*
 * course.h
 */

#ifndef _C_COURSE_H
#define _C_COURSE_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class cCourse
{
private:
    string m_name;

public:
    cCourse ();
	~cCourse ();

    void setName (string& sName);
    string getName (void);
};

#endif //_C_COURSE_H
