
#include "LoginCheck.h"

LoginCheck::LoginCheck() {
}

LoginCheck::~LoginCheck() {
}

void LoginCheck::check(Buf* pbuf) {
    struct sLogin login;
    memcpy(&login, ((MSG_HEAD*)pbuf->ptr())->cData(), sizeof(login));
    printf ("username = [%s], password = [%s]\n", login.username, login.password);
    int result = 0;

    switch(login.type) {
        case MCT_STUDENT:
            result = LoginCheck::login_student(pbuf->getfd(), login);
            break;
        case MCT_TEACHER:
            result = LoginCheck::login_teacher(pbuf->getfd(), login);
            break;
        case MCT_WHITEBOARD:
            result = LoginCheck::login_whiteboard(pbuf->getfd(), login);
            break;
        default:
            result = -1;
            break;
    }
#if 0
    // add
    Buf* p = SINGLE->bufpool.malloc();
    if (NULL == p) {
        printf("null buf\n");
        return;
    }

    p->setfd(pbuf->getfd());
#endif

    struct sLoginOutResult loginout;
    loginout.succeed = (0 == result) ? RES_SUCCEED : RES_FAIL;
    sprintf (loginout.message, "hellllllooooooo");
    MSG_HEAD* head = (MSG_HEAD*)pbuf->ptr();
    head->cLen = sizeof(MSG_HEAD) + sizeof(loginout);
    head->cType = CT_LoginResult;
    memcpy(head->cData(), &loginout, sizeof(loginout));
    pbuf->setsize (head->cLen);     // fix:
    SINGLE->sendqueue.enqueue(pbuf);
    return;
}

int LoginCheck::login_teacher(int fd, struct sLogin login) {
    string strpwd;
    string Account;
    try {
        MutexLockGuard guard(DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement (SQL_SELECT_TEACHER);
        pstmt->setString (1, login.username);
        ResultSet* prst = pstmt->executeQuery ();
        while (prst->next ()) {
            strpwd = prst->getString ("password");
#if 0
            //id = prst->getInt("teacher_id");
            Account = prst->getString("account");
            Account = prst->getString("first_name");
            Account = prst->getString("last_name");
#endif
        }
        delete prst;
        delete pstmt;
    }catch (SQLException e) {
    }

    if ((strcmp (login.password, strpwd.c_str()) == 0) && (!strlen (login.password))) {
        printf("teacher: login success!\n"); // ADD student_name to CLASS
        return 0;
    }
    return -1;
}

int LoginCheck::login_student(int fd, struct sLogin login) {
    string strpwd;
    string strFirstName;
    string strLastName;
    string strAccount;
    string strPictureName;
    int id = 0;
    try {
        MutexLockGuard guard(DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement(SQL_SELECT_STU);
        pstmt->setString(1, login.username);
        pstmt->setString(2, login.password);
        ResultSet* prst = pstmt->executeQuery();
        while(prst->next()) {
            strpwd = prst->getString("password");
            id = prst->getInt("student_id");
            strFirstName = prst->getString("first_name");
            strLastName = prst->getString("last_name");
            strAccount = prst->getString ("account");
            strPictureName = prst->getString ("picture_name");
        }
        delete prst;
        delete pstmt;
    }
    catch(SQLException e) {
        printf("[%s] %s\n",__FUNCTION__, e.what());
    }

    if ( 0 == strncmp(login.password, strpwd.c_str(), strpwd.size())) {
        printf("student: login success!\n"); // ADD student_name to CLASS

        CRoom* pClass = ROOMMANAGER->get_room_by_fd (fd);
        if (pClass == NULL) {
            LOG(ERROR) << "in login_student function. error: not found CLASS in CLASSMANAGER with fd" << endl;
            return -1;
        }

        printf("room[%p] get a sutdent\n", pClass);
        CStudent* pStudent = pClass->get_student_by_fd (fd);
        if (pStudent == NULL)
            LOG(ERROR) << "in login_student function. error: not found STUDENT in CLASSMANGER with fd" << endl;
        pStudent->setName (strFirstName, strLastName);
        pStudent->setAccount (strAccount);
        pStudent->setId (id);
        pStudent->setPictureName (strPictureName);
        pStudent->setOnLine (true);

        return 0;
    }
    printf("login failed: [%s][%s]", login.password, strpwd.c_str());
    return -1;
}

int LoginCheck::login_whiteboard(int fd, struct sLogin login) {
    string roomName;
    try {
        MutexLockGuard guard(DATABASE->m_mutex);
        PreparedStatement* pstmt = DATABASE->preStatement (SQL_SELECT_CLASSROOM1);
        pstmt->setString (1, login.username);
        ResultSet* prst = pstmt->executeQuery ();
        while (prst->next ()) {
            roomName = prst->getString ("classroom_name");
        }
        delete prst;
        delete pstmt;
    }catch(SQLException e) {
    }
    // ADD classroom_name and whiteboard_name to CLASS
    return 0;
}
