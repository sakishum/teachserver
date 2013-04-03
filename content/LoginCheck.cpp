
#include "LoginCheck.h"

LoginCheck::LoginCheck() {
}

LoginCheck::~LoginCheck() {
}

void LoginCheck::check(Buf* pbuf) {
    struct sLogin login;
    memcpy(&login, ((MSG_HEAD*)pbuf->ptr())->cData(), sizeof(login));
    printf ("%s, %s\n", login.username, login.password);
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
    string fName;
    string lName;
    int id = 0;
    try {
        PreparedStatement* pstmt = DATABASE->preStatement (SQL_SELECT_TEACHER);
        pstmt->setString (1, login.username);
        ResultSet* prst = pstmt->executeQuery ();
        while (prst->next ()) {
            strpwd = prst->getString ("password");
            id = prst->getInt("teacher_id");
            Account = prst->getString("account");
            Account = prst->getString("first_name");
            Account = prst->getString("last_name");
        }
        delete prst;
        delete pstmt;
    }catch (SQLException e) {
    }

    if ((strcmp (login.password, strpwd.c_str()) == 0) && (!strlen (login.password))) {
        SINGLE->map_id_fd.insert(id, fd);
        printf("teacher: login success!\n"); // ADD student_name to CLASS
        //CLASSMANAGER->enterRoom (NULL, NULL, login.username, NULL); // Create CLASS AND ADD teacher_name to CLASS
 #if 0
        cClass* pclass = new cClass();
        pclass->getTeacher()->setAccount(Account);
        pclass->getTeacher()->setSocket(fd);
        pclass->getTeacher()->setName(fName, lName);
        CLASSMANAGER->addClass(pclass);
#endif

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
    //int id = 0;
    try {
        PreparedStatement* pstmt = DATABASE->preStatement(SQL_SELECT_STU);
        pstmt->setString(1, login.username);
        pstmt->setString(2, login.password);
        ResultSet* prst = pstmt->executeQuery();
        while(prst->next()) {
            strpwd = prst->getString("password");
            //id = prst->getInt("student_id");
            strFirstName = prst->getString("first_name");
            strLastName = prst->getString("last_name");
            strAccount = prst->getString ("account");
            strPictureName = prst->getString ("picture_name");
        }
        delete prst;
        delete pstmt;
#if 0
        cStudent* pstudent = new cStudent();
        pstudent->setId(id);
        pstudent->setSocket(fd);
        pstudent->setName(strLastName, strFirstName);
        CLASSMANAGER->findClass()->addStudent(pstudent);
#endif
    }
    catch(SQLException e) {
    }

    if ((0 == strcmp(login.password, strpwd.c_str())) && (!strlen (login.password))) {
        printf("student: login success!\n"); // ADD student_name to CLASS
        //SINGLE->map_id_fd.insert(id, fd);
#if 0
        // find class by student fd
        CClass* pClass = CLASSMANAGER->get_class_by_fd (fd);
        if (pClass == NULL)
            LOG(ERROR) << "in login_student function. error: not found CLASS in CLASSMANAGER with fd" << endl;
        // add student to studentlist of CLASS
        CStudent* pStudent = pClass->get_student_by_fd (fd);
        if (pStudent == NULL)
            LOG(ERROR) << "in login_student function. error: not found STUDENT in CLASSMANGER with fd" << endl;
        pStudent->setName (strFirstName, strLastName);
        pStudent->setAccount (strAccount);
        pStudent->setId (id);
        pStudent->setPictureName (strPictureName);
        pStudent->setOnLine (true);
#endif
        return 0;
    }
    return -1;
}

int LoginCheck::login_whiteboard(int fd, struct sLogin login) {
    string roomName;
    try {
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
