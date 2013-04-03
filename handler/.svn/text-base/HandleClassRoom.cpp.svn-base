
/*
 * HandleClassRoom.cpp
 */

#include "HandleMessage.h"

#include "roommanager.h"
#include "class.h"
#include "protocol.h"
#include "Buf.h"

/*
=====================
 
=====================
*/
void CHandleMessage::handleTest (Buf* p)
{
    //todo:
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleChangeScene (Buf* p)
{
    //todo:
    printf ("change scene: %d\n", *(int *)((char *)p->ptr () + sizeof (MSG_HEAD)));
}

/*
=====================
 登录 (所有端)
=====================
*/
void CHandleMessage::handleLogin (Buf* p)
{
    //todo:
}

/*
=====================
 登录结果 (所有端)
=====================
*/
void CHandleMessage::handleLoginResult (Buf* p)
{
    //todo:
}

/*
=====================
 获得数据库中的课程信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseDBCount (Buf* p)
{
    //todo:
}

/*
=====================
 获得数据库中的课程信息 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseDB (Buf* p)
{
    //todo:
}

/*
=====================
 设置开启的课程列表 (教师端)
=====================
*/
void CHandleMessage::handleSetCourseGroup (Buf* p)
{
    //todo:
}

/*
=====================
 获得课程列表 (教师端和所有学生端)
=====================
*/
void CHandleMessage::handleGetCourseGroup (Buf* p)
{
    //todo:
}

/*
=====================
 获得课程列表的子项数量 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseItemCount (Buf* p)
{
    //todo:
}

/*
=====================
 获得课程列表的子项 (教师端)
=====================
*/
void CHandleMessage::handleGetCourseItem (Buf* p)
{
    //todo:
}

/*
=====================
 登出 (所有端)
=====================
*/
void CHandleMessage::handleLogout (Buf* p)
{
    //todo:
}

/*
=====================
 登出结果 (所有端)
=====================
*/
void CHandleMessage::handleLogoutReuslt (Buf* p)
{
    //todo:
}

/*
=====================
 获得教室数据库信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetClassRoomDBCount (Buf* p)
{
    //todo:
}

/*
=====================
 获得教室数据库信息 (教师端)
=====================
*/
void CHandleMessage::handleGetClassRoomDB (Buf* p)
{
    //todo:
}

/*
=====================
 获得教室年级数据库信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetGradeDBCount (Buf* p)
{
    //todo:
}

/*
=====================
 获得教室年级数据库信息 (教师端)
=====================
*/
void CHandleMessage::handleGetGradeDB (Buf* p)
{
    //todo:
}

/*
=====================
 获得班级信息数量 (教师端)
=====================
*/
void CHandleMessage::handleGetClassDBCount (Buf* p)
{
    //todo:
}

/*
=====================
 获得班级信息 (教师端)
=====================
*/
void CHandleMessage::handleGetClassDB (Buf* p)
{
    //todo:
}

/*
=====================
 进入教室 (所有学生端)
=====================
*/
void CHandleMessage::handleLoginClassRoom (Buf* p)
{
    //todo:
}

/*
=====================
 退出教室 (教师端和所有学生端)
=====================
*/
void CHandleMessage::handleLogoutClassRoom (Buf* p)
{
    //todo:
}

/*
=====================
 获得学生列表 (所有端)
=====================
*/
void CHandleMessage::handleGetStudentInfo (Buf* p)
{
    //todo:
}

/*
=====================
 获得所有学生列表数量 (所有端)
=====================
*/
void CHandleMessage::handleGetAllStudentInfoCount (Buf* p)
{
    cout << "CT_GetAllStudentInfoCount" << endl;
    CHandleMessage::postDBRecordCount (p, 5);
}

/*
=====================
 获得所有学生列表 (所有端)
=====================
*/
void CHandleMessage::handleGetAllStudentInfo (Buf* p)
{ 
    cout << "CT_GetAllStudentInfo" << endl;
    CHandleMessage::postDBRecord (p, 5);
}

/*
=====================
 早退 (教师端)
 早退通知给 (学生端)
=====================
*/
void CHandleMessage::handleLeaveEarly (Buf* p)
{
    //todo:
}

/*
=====================
 早退确认 (学生端) *
=====================
*/
void CHandleMessage::handleConfirmLeaveEarly (Buf* p)
{
    //todo:
}

/*
=====================
 获得教师信息 (所有学生端和教师端)
=====================
*/
void CHandleMessage::handleGetTeacherInfo (Buf* p)
{
    //todo:
}

/*
=====================
 锁定学生端 (教师端) *
 锁定学生端 (学生端) *
=====================
*/
void CHandleMessage::handleLockStudent (Buf* p)
{
    if (p == NULL)
        return;

    cout << "process: CT_LockStudent" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_LockStudent) {
        postTeacherToAllStudent (p, ST_LockStudent);
    }

    return;
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleSelectedClassRoom (Buf* p)
{
    //todo:
    printf ("CT_SelectedClassRoom: %d\n", *(int *)((char *)p->ptr () + sizeof (MSG_HEAD)));

    TSelectedClassRoom* pp = (TSelectedClassRoom*)((char*)p->ptr() + sizeof(MSG_HEAD));

    //CClass* pclass = CLASSMANAGER->get_class(pp->classroom_id);
    CRoom* proom = ROOMMANAGER->get_room(pp->classroom_id);
    if (MCT_STUDENT == pp->client_type) {
        CStudent* pstudent = new CStudent();
        proom->add_student(p->getfd(), pstudent);
    }
    if (MCT_WHITEBOARD == pp->client_type) {
        proom->set_white_fd(p->getfd());
    }
    p->reset();
    SINGLE->bufpool.free(p);
}

/*
=====================
 
=====================
*/
void CHandleMessage::handleCourseFinished (Buf* p)
{
    //todo:
}


/*
=====================
 CT_GetDBRecordFinished, // 请求所有数据库记录是否完成
 ST_GetDBRecordFinished, // 服务器回应数据库记录是否完成
=====================
*/
void CHandleMessage::handleDBRecordFinished (Buf* p)
{
    cout << "CT_GetDBRecordFinished and ST_GetDBRecordFinished" << endl;
    if (p == NULL);
        return;
#if 0
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();
    struct sDBRecordFinished finished;
    finished.iFlagFinished = 1;

    if (head->cType == CT_GetDBRecordFinished) {
        head->cLen = sizeof (MSG_HEAD) + sizeof (struct sDBRecordFinished);
        head->cType = ST_GetDBRecordFinished;
        memcpy (head->cData(), &finished, sizeof (struct sDBRecordFinished));
        p->setsize (head->cLen);
        SINGLE->sendqueue.enqueue (p);
    }
#endif
    return;
}
