#include "LoginCheck.h"
LoginCheck::LoginCheck() {
}

LoginCheck::~LoginCheck() {
}

void LoginCheck::check(Buf* pbuf) {
    struct sLogin login;

    memcpy(&login, ((MSG_HEAD*)pbuf->ptr())->cData(), sizeof(login));

    PreparedStatement* pstmt = DATABASE->preStatement(SQL_SELECT_STU);
    pstmt->setString(1, login.username);
    ResultSet* prst = pstmt->executeQuery();
    string strpwd;
    while(prst->next()) {
        strpwd = prst->getString(1);
    }

    if (0 == strcmp(login.password, strpwd.c_str())) {
        printf("login success!\n");
    }
}
