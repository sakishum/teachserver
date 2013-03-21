#ifndef LOGIN_H_
#define LOGIN_H_
#include "database.h"
#include "protocol.h"
#include "Buf.h"
#include "SQL.h"
class LoginCheck{
    LoginCheck();
    ~LoginCheck();
    void check(Buf* pbuf);
};
#endif
