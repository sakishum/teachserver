#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include "protocol.h"

#define SERV_IP "127.0.0.1"
#define SERV_PORT 9999 
#define CON_NUM 500
#include "database.h"

#include "gtest/gtest.h"


TEST(database, Basic) {
      CONFIG->readconfig("./../config.lua");
      DATABASE->Init(CONFIG->db_host, CONFIG->db_username, CONFIG->db_password, CONFIG->db_database);
      Statement* pstmt = DATABASE->getStatement();
      ResultSet* rest1 = pstmt->executeQuery("SELECT student_id FROM student");
      int i = 0;
      while(rest1->next()){
          i++;
      }

      ResultSet* rest2 = pstmt->executeQuery("SELECT count(1) FROM student");
      rest2->next();
      int j = rest2->getInt(1);
      delete rest1;
      delete rest2;
      delete pstmt;
      EXPECT_EQ(i,j);
}

TEST(database, pre) {
  //CONFIG->readconfig("./../config.lua");
  //DATABASE->Init(CONFIG->db_host, CONFIG->db_username, CONFIG->db_password, CONFIG->db_database);
    PreparedStatement* p = DATABASE->preStatement("select first_name from student where student_id= ?");
    p->setInt(1, 1);
    ResultSet* prest = p->executeQuery();
    while(prest->next()) {
        printf("%s\n", prest->getString(1).c_str());
    }
    delete prest;
    delete p;
}
