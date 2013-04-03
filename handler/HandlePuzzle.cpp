
/*
 * HandlePuzzle.cpp
 */

#include "HandleMessage.h"

#include "protocol.h"
#include "Buf.h"

/*
=====================
 点击拼图开始 (教师端)
 发送拼图游戏开始信息 (学生端和白板端)
=====================
*/
void CHandleMessage::handlePuzzle_GameStart (Buf* p)
{
    //todo:
}

/*
=====================
 获得拼图是否正确的状态 (学生端) *
 发送拼图是否正确的状态 (白板端) *
=====================
*/
void CHandleMessage::handlePuzzle_IconStatus (Buf* p)
{
#ifdef _EXECUTE_
    if (p == NULL)
        return;

    cout << "process: CT_Puzzle_IconStatus" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_Puzzle_IconStatus) {
        CHandleMessage::postTeacherToWhite (p, ST_Puzzle_IconStatus);
    }

    return;
#endif
}

/*
=====================
 拼图播放 (学生端) *
 拼图播放 (白板端) *
=====================
*/
void CHandleMessage::handlePuzzle_Play (Buf* p)
{
#ifdef _EXECUTE_
    if (p == NULL)
        return;

    cout << "process: CT_Puzzle_Play" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_Puzzle_Play) {
        CHandleMessage::postTeacherToWhite (p, ST_Puzzle_Play);
    }

    return;
#endif
}

/*
=====================
 拼图暂停 (学生端) *
 拼图暂停 (白板端) *
=====================
*/
void CHandleMessage::handlePuzzle_Pause (Buf* p)
{
#ifdef _EXECUTE_
    if (p == NULL)
        return;

    cout << "process: CT_Puzzle_Pause" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_Puzzle_Pause) {
        CHandleMessage::postTeacherToWhite (p, ST_Puzzle_Pause);
    }

    return;
#endif
}

/*
=====================
 拼图恢复 (学生端) *
 拼图恢复 (白板端) *
=====================
*/
#if 0
void CHandleMessage::handlePuzzle_Resume (Buf* p)
{
#ifdef _EXECUTE_
    if (p == NULL)
        return;

    cout << "process: CT_Puzzle_Resume" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_Puzzle_Resume) {
        CHandleMessage::postTeacherToWhite (p, ST_Puzzle_Resume);
    }

    return;
#endif
}
#endif

/*
=====================
 拼图区中移动某一拼图块 (客户端) **
 拼图区中移动某一拼图块 (白板端) **
=====================
*/
void CHandleMessage::handlePuzzle_MovePic (Buf* p)
{
    //todo:
}

/*
=====================
 拼图区中删除某一拼图块 (客户端) **
 拼图区中删除某一拼图块 (白板端) **
=====================
*/
void CHandleMessage::handlePuzzle_DeletePic (Buf* p)
{
    //todo:
}

/*
=====================
 拼图区中添加某一拼图块 (客户端) **
 拼图区中添加某一拼图块 (白板端) **
=====================
*/
void CHandleMessage::handlePuzzle_AddPic (Buf* p)
{
    //todo:
}

/*
=====================
 拼图的结果 (教师端) &*
=====================
*/
void CHandleMessage::handlePuzzle_CalcScore (Buf* p)
{
    //todo:
}

/*
=====================
 结束拼图课程 (教师端) *
 结束拼图课程 (白板端和所有学生端) *
=====================
*/
void CHandleMessage::handlePuzzle_EndGame (Buf* p)
{
#ifdef _EXECUTE_
    if (p == NULL)
        return;

    cout << "process: CT_Puzzle_EndGame" << endl;
    MSG_HEAD* head = (MSG_HEAD*)p->ptr();

    if (head->cType == CT_Puzzle_EndGame) {
        CHandleMessage::postTeacherToWhite (p, ST_Puzzle_EndGame);
    }

    return;
#endif
}
