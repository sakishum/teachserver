/*
@desc		the db header
@author		cacls 
@date		2012/12/24
@copyright	sxkj
*/

#ifndef _DATABASE_H_
#define _DATABASE_H_
#include <string>
#include <iostream>


#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <glog/logging.h>

#include "Config.h"

using namespace sql;
using namespace std;

class DataBase
{
public:
	~DataBase();
	bool Init(string host, string user_name, string password, string database);
  Connection* getConnection();
  Statement* getStatement();
  string getDatabase();
  static DataBase* instance();
private:
  DataBase();
  Driver* m_pDriver;
  Connection* m_pConn;
	string m_host;
	string m_user_name;
	string m_password;
	string m_database;
  static DataBase *pinstance;
};
#define DATABASE DataBase::instance()
#endif
